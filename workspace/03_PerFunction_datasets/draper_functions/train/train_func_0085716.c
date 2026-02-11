IsReachable(const SUnit *SU,
                                             const SUnit *TargetSU) {


  int UpperBound, LowerBound;
  LowerBound = Node2Index[TargetSU->NodeNum];
  UpperBound = Node2Index[SU->NodeNum];
  bool HasLoop = false;

  if (LowerBound < UpperBound) {
    Visited.reset();

    DFS(TargetSU, UpperBound, HasLoop);
  }
  return HasLoop;
}
