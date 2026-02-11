isPhysDefTriviallyDead(unsigned Reg,
                                   MachineBasicBlock::const_iterator I,
                                   MachineBasicBlock::const_iterator E) const {
  unsigned LookAheadLeft = LookAheadLimit;
  while (LookAheadLeft) {

    while (I != E && I->isDebugValue())
      ++I;

    if (I == E)

      return true;

    bool SeenDef = false;
    for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i) {
      const MachineOperand &MO = I->getOperand(i);
      if (MO.isRegMask() && MO.clobbersPhysReg(Reg))
        SeenDef = true;
      if (!MO.isReg() || !MO.getReg())
        continue;
      if (!TRI->regsOverlap(MO.getReg(), Reg))
        continue;
      if (MO.isUse())

        return false;
      SeenDef = true;
    }
    if (SeenDef)


      return true;

    --LookAheadLeft;
    ++I;
  }
  return false;
}
