isLiveOut(unsigned r, MachineBasicBlock* MBB,
                      LiveIntervals& LI) {
  for (MachineBasicBlock::succ_iterator PI = MBB->succ_begin(),
       E = MBB->succ_end(); PI != E; ++PI)
    if (isLiveIn(r, *PI, LI))
      return true;

  return false;
}
