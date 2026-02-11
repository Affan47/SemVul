isALU(const MachineInstr *MI) const {
    if (TII->isALUInstr(MI->getOpcode()))
      return true;
    if (TII->isVector(*MI) || TII->isCubeOp(MI->getOpcode()))
      return true;
    switch (MI->getOpcode()) {
    case AMDGPU::PRED_X:
    case AMDGPU::INTERP_PAIR_XY:
    case AMDGPU::INTERP_PAIR_ZW:
    case AMDGPU::INTERP_VEC_LOAD:
    case AMDGPU::COPY:
    case AMDGPU::DOT_4:
      return true;
    default:
      return false;
    }
  }
