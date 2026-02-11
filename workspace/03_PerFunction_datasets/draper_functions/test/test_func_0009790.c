printDSOffset(const MCInst *MI, unsigned OpNo,
                                      raw_ostream &O) {
  uint16_t Imm = MI->getOperand(OpNo).getImm();
  if (Imm != 0) {
    O << " offset:";
    printU16ImmDecOperand(MI, OpNo, O);
  }
}
