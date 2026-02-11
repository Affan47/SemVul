Schedule() {

  BuildSchedGraph(AA);

  if (AntiDepBreak != NULL) {
    unsigned Broken =
      AntiDepBreak->BreakAntiDependencies(SUnits, Begin, InsertPos,
                                          InsertPosIndex);

    if (Broken != 0) {


      SUnits.clear();
      Sequence.clear();
      EntrySU = SUnit();
      ExitSU = SUnit();
      BuildSchedGraph(AA);

      NumFixedAnti += Broken;
    }
  }

  DEBUG(dbgs() << "********** List Scheduling **********\n");
  DEBUG(for (unsigned su = 0, e = SUnits.size(); su != e; ++su)
          SUnits[su].dumpAll(this));

  AvailableQueue.initNodes(SUnits);
  ListScheduleTopDown();
  AvailableQueue.releaseState();
}
