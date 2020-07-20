// Copyright 2020 The TensorFlow Runtime Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//===- static_registration.cc ---------------------------------------------===//
//
// This file uses a static constructor to automatically register all of the
// kernels in this directory.  This can be used to simplify clients that don't
// care about selective registration of kernels.
//
//===----------------------------------------------------------------------===//

#include "tfrt/common/ops/test/metadata_functions.h"
#include "tfrt/gpu/core_runtime/gpu_op_registry.h"
#include "tfrt/gpu/ops/test/gpu_ops_and_kernels.h"

namespace tfrt {
static void RegisterMetadataFn(GpuOpRegistry* registry) {
  for (const std::pair<llvm::StringRef, OpMetadataFn>& md_function :
       GetAllTestMetadataFunctions()) {
    registry->AddMetadataFn(md_function.first, md_function.second);
  }
}

TFRT_STATIC_GPU_OP_REGISTRATION(RegisterTestGPUOps);
TFRT_STATIC_GPU_OP_REGISTRATION(RegisterMetadataFn);

}  // namespace tfrt