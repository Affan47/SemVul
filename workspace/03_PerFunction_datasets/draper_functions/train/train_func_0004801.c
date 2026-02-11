bumpNode(SUnit *SU) {
  bool startNewCycle = false;


  if (HazardRec->isEnabled()) {
    if (!isTop() && SU->isCall) {


      HazardRec->Reset();
    }
    HazardRec->EmitInstruction(SU);
  }


  startNewCycle = ResourceModel->reserveResources(SU);


  IssueCount += SchedModel->getNumMicroOps(SU->getInstr());
  if (startNewCycle) {
    DEBUG(dbgs() << "*** Max instrs at cycle " << CurrCycle << '\n');
    bumpCycle();
  }
  else
    DEBUG(dbgs() << "*** IssueCount " << IssueCount
          << " at cycle " << CurrCycle << '\n');
}
