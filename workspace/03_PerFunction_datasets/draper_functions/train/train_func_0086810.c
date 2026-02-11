canReadVGPR(const MachineInstr &MI, unsigned OpNo) const {
  switch (MI.getOpcode()) {
  case AMDGPU::COPY:
  case AMDGPU::REG_SEQUENCE:
  case AMDGPU::PHI:
  case AMDGPU::INSERT_SUBREG:
    return RI.hasVGPRs(getOpRegClass(MI, 0));
  default:
    return RI.hasVGPRs(getOpRegClass(MI, OpNo));
  }
}
