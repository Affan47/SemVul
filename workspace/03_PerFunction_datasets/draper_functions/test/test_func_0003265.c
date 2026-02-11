getDestEquivalentVGPRClass(
  const MachineInstr &Inst) const {
  const TargetRegisterClass *NewDstRC = getOpRegClass(Inst, 0);

  switch (Inst.getOpcode()) {


  case AMDGPU::COPY:
  case AMDGPU::PHI:
  case AMDGPU::REG_SEQUENCE:
  case AMDGPU::INSERT_SUBREG:
    if (RI.hasVGPRs(NewDstRC))
      return nullptr;

    NewDstRC = RI.getEquivalentVGPRClass(NewDstRC);
    if (!NewDstRC)
      return nullptr;
    return NewDstRC;
  default:
    return NewDstRC;
  }
}
