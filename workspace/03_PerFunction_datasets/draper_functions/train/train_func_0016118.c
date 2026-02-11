printVOPDst(const MCInst *MI, unsigned OpNo,
                                    raw_ostream &O) {
  if (MII.get(MI->getOpcode()).TSFlags & SIInstrFlags::VOP3)
    O << "_e64 ";
  else
    O << "_e32 ";

  printOperand(MI, OpNo, O);
}
