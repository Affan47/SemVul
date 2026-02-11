getModRefInfo(const StoreInst *S, const Location &Loc) {

  if (!S->isUnordered())
    return ModRef;


  if (!alias(getLocation(S), Loc))
    return NoModRef;


  if (pointsToConstantMemory(Loc))
    return NoModRef;


  return Mod;
}
