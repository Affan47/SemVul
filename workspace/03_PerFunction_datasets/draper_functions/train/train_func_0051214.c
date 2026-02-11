ReleaseSucc(SUnit *SU, SDep *SuccEdge) {
  SUnit *SuccSU = SuccEdge->getSUnit();

#ifndef NDEBUG
  if (SuccSU->NumPredsLeft == 0) {
    dbgs() << "*** Scheduling failed! ***\n";
    SuccSU->dump(this);
    dbgs() << " has been released too many times!\n";
    llvm_unreachable(0);
  }
#endif
  --SuccSU->NumPredsLeft;


  SuccSU->setDepthToAtLeast(SU->getDepth() + SuccEdge->getLatency());


  if (SuccSU->NumPredsLeft == 0 && SuccSU != &ExitSU)
    PendingQueue.push_back(SuccSU);
}
