splitInBlock(MachineBasicBlock &B) {
  bool Changed = false;
  MachineBasicBlock::iterator I, E, NextI;
  for (I = B.begin(), E = B.end(); I != E; I = NextI) {
    NextI = std::next(I);
    if (isCondset(I))
      Changed |= split(I);
  }
  return Changed;
}
