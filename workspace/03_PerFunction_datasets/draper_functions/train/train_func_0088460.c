isLegalToSplitMBBAt(MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator MBBI) const {
  while (MBBI->isDebugValue()) {
    ++MBBI;
    if (MBBI == MBB.end())
      return false;
  }

  unsigned PredReg = 0;
  return getITInstrPredicate(MBBI, PredReg) == ARMCC::AL;
}
