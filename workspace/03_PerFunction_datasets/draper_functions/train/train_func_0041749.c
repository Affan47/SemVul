SurveyUses(const Value *V, UseVector &MaybeLiveUses) {

  Liveness Result = MaybeLive;

  for (const Use &U : V->uses()) {
    Result = SurveyUse(&U, MaybeLiveUses);
    if (Result == Live)
      break;
  }
  return Result;
}
