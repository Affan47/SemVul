getARMBranchTargetOpValue(const MCInst &MI, unsigned OpIdx,
                          SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const {
  const MCOperand MO = MI.getOperand(OpIdx);
  if (MO.isExpr()) {
    if (HasConditionalBranch(MI))
      return ::getBranchTargetOpValue(MI, OpIdx,
                                      ARM::fixup_arm_condbranch, Fixups, STI);
    return ::getBranchTargetOpValue(MI, OpIdx,
                                    ARM::fixup_arm_uncondbranch, Fixups, STI);
  }

  return MO.getImm() >> 2;
}
