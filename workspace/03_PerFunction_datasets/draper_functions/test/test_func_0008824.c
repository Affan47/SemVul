propagateUsesAroundLoop(MachineBasicBlock* MBB, MachineLoop* LP) {
  if (! MBB || !LP)
    return;

  std::vector<MachineBasicBlock*> loopBlocks = LP->getBlocks();
  for (unsigned i = 0, e = loopBlocks.size(); i != e; ++i) {
    MachineBasicBlock* LBB = loopBlocks[i];
    if (LBB == MBB)
      continue;
    if (CSRUsed[LBB].contains(CSRUsed[MBB]))
      continue;
    CSRUsed[LBB] |= CSRUsed[MBB];
  }
}
