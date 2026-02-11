getThumbAdrLabelOpValue(const MCInst &MI, unsigned OpIdx,
                   SmallVectorImpl<MCFixup> &Fixups) const {
  const MCOperand MO = MI.getOperand(OpIdx);
  if (MO.isExpr())
    return ::getBranchTargetOpValue(MI, OpIdx, ARM::fixup_thumb_adr_pcrel_10,
                                    Fixups);
  return MO.getImm();
}
