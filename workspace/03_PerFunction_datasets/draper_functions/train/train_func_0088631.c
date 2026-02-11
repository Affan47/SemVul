isRevCopyChain(unsigned FromReg, unsigned ToReg,
                                               int Maxlen) {
  unsigned TmpReg = FromReg;
  for (int i = 0; i < Maxlen; i++) {
    MachineInstr *Def = getSingleDef(TmpReg, MBB, MRI);
    if (!Def || !Def->isCopy())
      return false;

    TmpReg = Def->getOperand(1).getReg();

    if (TmpReg == ToReg)
      return true;
  }
  return false;
}
