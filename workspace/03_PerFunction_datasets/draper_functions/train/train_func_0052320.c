ReleasePred(SUnit *SU, const SDep *PredEdge) {
  SUnit *PredSU = PredEdge->getSUnit();

#ifndef NDEBUG
  if (PredSU->NumSuccsLeft == 0) {
    dbgs() << "*** Scheduling failed! ***\n";
    PredSU->dump(this);
    dbgs() << " has been released too many times!\n";
    llvm_unreachable(nullptr);
  }
#endif
  --PredSU->NumSuccsLeft;

  if (!forceUnitLatencies()) {


    PredSU->setHeightToAtLeast(SU->getHeight() + PredEdge->getLatency());
  }


  if (PredSU->NumSuccsLeft == 0 && PredSU != &EntrySU) {
    PredSU->isAvailable = true;

    unsigned Height = PredSU->getHeight();
    if (Height < MinAvailableCycle)
      MinAvailableCycle = Height;

    if (isReady(PredSU)) {
      AvailableQueue->push(PredSU);
    }


    else if (!PredSU->isPending) {
      PredSU->isPending = true;
      PendingQueue.push_back(PredSU);
    }
  }
}
