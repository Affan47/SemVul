InitBottomUp(ARCMDKindCache &Cache, Instruction *I) {


  bool NestingDetected = false;
  if (GetSeq() == S_Release || GetSeq() == S_MovableRelease) {
    DEBUG(dbgs() << "        Found nested releases (i.e. a release pair)\n");
    NestingDetected = true;
  }

  MDNode *ReleaseMetadata =
      I->getMetadata(Cache.get(ARCMDKindID::ImpreciseRelease));
  Sequence NewSeq = ReleaseMetadata ? S_MovableRelease : S_Release;
  ResetSequenceProgress(NewSeq);
  SetReleaseMetadata(ReleaseMetadata);
  SetKnownSafe(HasKnownPositiveRefCount());
  SetTailCallRelease(cast<CallInst>(I)->isTailCall());
  InsertCall(I);
  SetKnownPositiveRefCount();
  return NestingDetected;
}
