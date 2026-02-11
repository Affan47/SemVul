collectEphemeralValues(
    const Loop *L, AssumptionCache *AC,
    SmallPtrSetImpl<const Value *> &EphValues) {
  SmallVector<const Value *, 16> WorkSet;

  for (auto &AssumeVH : AC->assumptions()) {
    if (!AssumeVH)
      continue;
    Instruction *I = cast<Instruction>(AssumeVH);


    if (!L->contains(I->getParent()))
      continue;

    WorkSet.push_back(I);
  }

  completeEphemeralValues(WorkSet, EphValues);
}
