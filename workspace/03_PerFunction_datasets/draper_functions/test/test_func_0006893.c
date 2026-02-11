RemoveBranch(MachineBasicBlock &MBB) const
{
  MachineBasicBlock::iterator I = MBB.end();
  unsigned Count = 0;
  while (I != MBB.begin()) {
    --I;

    if (I->isDebugValue())
      continue;

    if (I->getOpcode() != SP::BA
        && I->getOpcode() != SP::BCOND
        && I->getOpcode() != SP::FBCOND)
      break;

    I->eraseFromParent();
    I = MBB.end();
    ++Count;
  }
  return Count;
}
