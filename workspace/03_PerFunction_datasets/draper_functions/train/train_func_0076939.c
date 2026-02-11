propagate(const SCEV *&Src,
                                   const SCEV *&Dst,
                                   SmallBitVector &Loops,
                                   SmallVectorImpl<Constraint> &Constraints,
                                   bool &Consistent) {
  bool Result = false;
  for (int LI = Loops.find_first(); LI >= 0; LI = Loops.find_next(LI)) {
    DEBUG(dbgs() << "\t    Constraint[" << LI << "] is");
    DEBUG(Constraints[LI].dump(dbgs()));
    if (Constraints[LI].isDistance())
      Result |= propagateDistance(Src, Dst, Constraints[LI], Consistent);
    else if (Constraints[LI].isLine())
      Result |= propagateLine(Src, Dst, Constraints[LI], Consistent);
    else if (Constraints[LI].isPoint())
      Result |= propagatePoint(Src, Dst, Constraints[LI]);
  }
  return Result;
}
