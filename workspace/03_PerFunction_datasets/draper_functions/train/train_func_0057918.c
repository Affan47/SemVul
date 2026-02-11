addCallSite(CallSite CS, AliasAnalysis &AA) {
  CallSites.push_back(CS.getInstruction());

  AliasAnalysis::ModRefBehavior Behavior = AA.getModRefBehavior(CS);
  if (Behavior == AliasAnalysis::DoesNotAccessMemory)
    return;
  else if (Behavior == AliasAnalysis::OnlyReadsMemory) {
    AliasTy = MayAlias;
    AccessTy |= Refs;
    return;
  }


  AliasTy = MayAlias;
  AccessTy = ModRef;
}
