selectVectorRegClassID(unsigned NumVectorElts, bool UseVGPR) {
  if (UseVGPR) {
    switch (NumVectorElts) {
    case 1:
      return AMDGPU::VGPR_32RegClassID;
    case 2:
      return AMDGPU::VReg_64RegClassID;
    case 4:
      return AMDGPU::VReg_128RegClassID;
    case 8:
      return AMDGPU::VReg_256RegClassID;
    case 16:
      return AMDGPU::VReg_512RegClassID;
    }
  }

  switch (NumVectorElts) {
  case 1:
    return AMDGPU::SReg_32RegClassID;
  case 2:
    return AMDGPU::SReg_64RegClassID;
  case 4:
    return AMDGPU::SReg_128RegClassID;
  case 8:
    return AMDGPU::SReg_256RegClassID;
  case 16:
    return AMDGPU::SReg_512RegClassID;
  }

  llvm_unreachable("invalid vector size");
}
