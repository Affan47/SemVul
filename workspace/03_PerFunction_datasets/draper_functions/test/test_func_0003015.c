evaluateBranch(const MCInst &Inst, uint64_t Addr,
                                         uint64_t Size) const {
  if (Inst.getNumOperands() == 0 ||
      Info->get(Inst.getOpcode()).OpInfo[0].OperandType != MCOI::OPERAND_PCREL)
    return -1ULL;

  int64_t Imm = Inst.getOperand(0).getImm();
  return Addr+Size+Imm;
}
