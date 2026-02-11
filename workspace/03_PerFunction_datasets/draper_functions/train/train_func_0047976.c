aliasSelect(const SelectInst *SI, unsigned SISize,
                                const Value *V2, unsigned V2Size) {


  if (!Visited.insert(SI))
    return MayAlias;


  if (const SelectInst *SI2 = dyn_cast<SelectInst>(V2))
    if (SI->getCondition() == SI2->getCondition()) {
      AliasResult Alias =
        aliasCheck(SI->getTrueValue(), SISize,
                   SI2->getTrueValue(), V2Size);
      if (Alias == MayAlias)
        return MayAlias;
      AliasResult ThisAlias =
        aliasCheck(SI->getFalseValue(), SISize,
                   SI2->getFalseValue(), V2Size);
      if (ThisAlias != Alias)
        return MayAlias;
      return Alias;
    }


  AliasResult Alias =
    aliasCheck(V2, V2Size, SI->getTrueValue(), SISize);
  if (Alias == MayAlias)
    return MayAlias;


  Visited.erase(V2);

  AliasResult ThisAlias =
    aliasCheck(V2, V2Size, SI->getFalseValue(), SISize);
  if (ThisAlias != Alias)
    return MayAlias;
  return Alias;
}
