printOperandAndMods(const MCInst *MI, unsigned OpNo,
                                            raw_ostream &O) {
  unsigned InputModifiers = MI->getOperand(OpNo).getImm();
  if (InputModifiers & SISrcMods::NEG)
    O << '-';
  if (InputModifiers & SISrcMods::ABS)
    O << '|';
  printOperand(MI, OpNo + 1, O);
  if (InputModifiers & SISrcMods::ABS)
    O << '|';
}
