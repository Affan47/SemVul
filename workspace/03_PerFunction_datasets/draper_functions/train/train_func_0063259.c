getAddrMode6OffsetOpValue(const MCInst &MI, unsigned Op,
                          SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(Op);
  if (MO.getReg() == 0) return 0x0D;
  return CTX.getRegisterInfo()->getEncodingValue(MO.getReg());
}
