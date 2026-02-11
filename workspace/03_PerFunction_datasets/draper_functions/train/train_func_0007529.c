Schedule() {
  DEBUG(dbgs() << "********** List Scheduling **********\n");


  BuildSchedGraph(NULL);

  AvailableQueue->initNodes(SUnits);

  ListScheduleTopDown();

  AvailableQueue->releaseState();
}
