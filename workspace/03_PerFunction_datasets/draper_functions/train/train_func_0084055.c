nextEvent()
{
  while (eventQueueEmpty()) {
    switch (phase()) {
    case noPhase:
      return 0;
    case initPhase:
      doInit();
      break;
    case prologPhase:
      doProlog();
      break;
    case declSubsetPhase:
      doDeclSubset();
      break;
    case instanceStartPhase:
      doInstanceStart();
      break;
    case contentPhase:
      doContent();
      break;
    }
  }
  return eventQueueGet();
}
