isPredicated(const MachineInstr *MI) const {
  int idx = MI->findFirstPredOperandIdx();
  if (idx < 0)
    return false;

  unsigned Reg = MI->getOperand(idx).getReg();
  switch (Reg) {
  default: return false;
  case AMDGPU::PRED_SEL_ONE:
  case AMDGPU::PRED_SEL_ZERO:
  case AMDGPU::PREDICATE_BIT:
    return true;
  }
}
