Extract(Value *Idx, GetElementPtrInst *GEP,
                                        User *&UserChainTail,
                                        const DominatorTree *DT) {
  ConstantOffsetExtractor Extractor(GEP, DT);

  APInt ConstantOffset =
      Extractor.find(Idx,  false,  false,
                     GEP->isInBounds());
  if (ConstantOffset == 0) {
    UserChainTail = nullptr;
    return nullptr;
  }

  Value *IdxWithoutConstOffset = Extractor.rebuildWithoutConstOffset();
  UserChainTail = Extractor.UserChain.back();
  return IdxWithoutConstOffset;
}
