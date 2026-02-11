getAddrMode6OneLane32AddressOpValue(const MCInst &MI, unsigned Op,
                                    SmallVectorImpl<MCFixup> &Fixups) const {
  const MCOperand &Reg = MI.getOperand(Op);
  const MCOperand &Imm = MI.getOperand(Op + 1);

  unsigned RegNo = getARMRegisterNumbering(Reg.getReg());
  unsigned Align = 0;

  switch (Imm.getImm()) {
  default: break;
  case 2:
  case 4:
  case 8:
  case 16: Align = 0x00; break;
  case 32: Align = 0x03; break;
  }

  return RegNo | (Align << 4);
}
