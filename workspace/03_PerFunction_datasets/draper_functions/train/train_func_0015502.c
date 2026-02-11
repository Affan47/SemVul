checkSATCore()
{
  DebugAssert(d_queue.empty(), "checkSATCore[start]: Expected empty queue");
  DebugAssert(d_queueSE.empty(), "checkSATCore[start]: Expected empty queue");
  DebugAssert(!d_inCheckSATCore, "Recursive call to checkSATCore is not allowed!");
  ScopeWatcher sw(&d_inCheckSATCore);
  IF_DEBUG(debugger.counter("DP checkSAT(fullEffort) calls")++;)
  DebugAssert(d_update_thms.empty() && d_update_data.empty(),
              "addFact[start]: Expected empty update list");

  bool lemmas = processFactQueue(FULL);

  DebugAssert(d_queue.empty(), "checkSATCore[start]: Expected empty queue");
  DebugAssert(d_queueSE.empty(), "checkSATCore[start]: Expected empty queue");
  DebugAssert(d_update_thms.empty() && d_update_data.empty(),
              "addFact[end]: Expected empty update list");

  return !lemmas;
}
