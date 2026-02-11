Merge(const PtrState &Other, bool TopDown) {
  Seq = MergeSeqs(Seq, Other.Seq, TopDown);
  RefCount = std::min(RefCount, Other.RefCount);
  NestCount = std::min(NestCount, Other.NestCount);


  if (RRI.IsRetainBlock != Other.RRI.IsRetainBlock)
    Seq = S_None;


  if (Seq == S_None) {
    RRI.clear();
  } else if (RRI.Partial || Other.RRI.Partial) {


    Seq = S_None;
    RRI.clear();
  } else {

    if (RRI.ReleaseMetadata != Other.RRI.ReleaseMetadata)
      RRI.ReleaseMetadata = 0;

    RRI.CopyOnEscape = RRI.CopyOnEscape && Other.RRI.CopyOnEscape;
    RRI.KnownSafe = RRI.KnownSafe && Other.RRI.KnownSafe;
    RRI.IsTailCallRelease = RRI.IsTailCallRelease && Other.RRI.IsTailCallRelease;
    RRI.Calls.insert(Other.RRI.Calls.begin(), Other.RRI.Calls.end());


    RRI.Partial = RRI.ReverseInsertPts.size() !=
                  Other.RRI.ReverseInsertPts.size();
    for (SmallPtrSet<Instruction *, 2>::const_iterator
         I = Other.RRI.ReverseInsertPts.begin(),
         E = Other.RRI.ReverseInsertPts.end(); I != E; ++I)
      RRI.Partial |= RRI.ReverseInsertPts.insert(*I);
  }
}
