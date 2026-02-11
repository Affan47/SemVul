recomputeLiveInValues(
    Function &F, DominatorTree &DT, Pass *P, ArrayRef<CallSite> toUpdate,
    MutableArrayRef<struct PartiallyConstructedSafepointRecord> records) {


  GCPtrLivenessData RevisedLivenessData;
  computeLiveInValues(DT, F, RevisedLivenessData);
  for (size_t i = 0; i < records.size(); i++) {
    struct PartiallyConstructedSafepointRecord &info = records[i];
    const CallSite &CS = toUpdate[i];
    recomputeLiveInValues(RevisedLivenessData, CS, info);
  }
}
