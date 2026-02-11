aliasSelect(const SelectInst *SI, uint64_t SISize,
                                       const AAMDNodes &SIAAInfo,
                                       const Value *V2, uint64_t V2Size,
                                       const AAMDNodes &V2AAInfo) {


  if (const SelectInst *SI2 = dyn_cast<SelectInst>(V2))
    if (SI->getCondition() == SI2->getCondition()) {
      AliasResult Alias = aliasCheck(SI->getTrueValue(), SISize, SIAAInfo,
                                     SI2->getTrueValue(), V2Size, V2AAInfo);
      if (Alias == MayAlias)
        return MayAlias;
      AliasResult ThisAlias =
          aliasCheck(SI->getFalseValue(), SISize, SIAAInfo,
                     SI2->getFalseValue(), V2Size, V2AAInfo);
      return MergeAliasResults(ThisAlias, Alias);
    }


  AliasResult Alias =
      aliasCheck(V2, V2Size, V2AAInfo, SI->getTrueValue(), SISize, SIAAInfo);
  if (Alias == MayAlias)
    return MayAlias;

  AliasResult ThisAlias =
      aliasCheck(V2, V2Size, V2AAInfo, SI->getFalseValue(), SISize, SIAAInfo);
  return MergeAliasResults(ThisAlias, Alias);
}
