printThumbSRImm(const MCInst *MI, unsigned OpNum,
                                     const MCSubtargetInfo &STI,
                                     raw_ostream &O) {
  unsigned Imm = MI->getOperand(OpNum).getImm();
  O << markup("<imm:") << "#" << formatImm((Imm == 0 ? 32 : Imm))
    << markup(">");
}
