getNamedOperand(MachineInstr &MI,
                                             unsigned OperandName) const {
  int Idx = AMDGPU::getNamedOperandIdx(MI.getOpcode(), OperandName);
  if (Idx == -1)
    return nullptr;

  return &MI.getOperand(Idx);
}
