Schedule() {
  DEBUG(dbgs() << "********** List Scheduling **********\n");

  NumLiveRegs = 0;
  LiveRegDefs.resize(TRI->getNumRegs(), nullptr);
  LiveRegCycles.resize(TRI->getNumRegs(), 0);


  BuildSchedGraph(nullptr);

  DEBUG(for (unsigned su = 0, e = SUnits.size(); su != e; ++su)
          SUnits[su].dumpAll(this));


  ListScheduleBottomUp();
}
