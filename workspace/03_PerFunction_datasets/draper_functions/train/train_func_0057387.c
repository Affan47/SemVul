FindAliasInfo(SDNode *N,
                        SDValue &Ptr, int64_t &Size,
                        const Value *&SrcValue,
                        int &SrcValueOffset,
                        unsigned &SrcValueAlign) const {
  if (LoadSDNode *LD = dyn_cast<LoadSDNode>(N)) {
    Ptr = LD->getBasePtr();
    Size = LD->getMemoryVT().getSizeInBits() >> 3;
    SrcValue = LD->getSrcValue();
    SrcValueOffset = LD->getSrcValueOffset();
    SrcValueAlign = LD->getOriginalAlignment();
    return true;
  } else if (StoreSDNode *ST = dyn_cast<StoreSDNode>(N)) {
    Ptr = ST->getBasePtr();
    Size = ST->getMemoryVT().getSizeInBits() >> 3;
    SrcValue = ST->getSrcValue();
    SrcValueOffset = ST->getSrcValueOffset();
    SrcValueAlign = ST->getOriginalAlignment();
  } else {
    llvm_unreachable("FindAliasInfo expected a memory operand");
  }

  return false;
}
