isSafeToMove(const TargetInstrInfo *TII,
                                AliasAnalysis *AA,
                                bool &SawStore) const {

  if (TID->mayStore() || TID->isCall()) {
    SawStore = true;
    return false;
  }
  if (TID->isTerminator() || TID->hasUnmodeledSideEffects())
    return false;


  if (TID->mayLoad() && !isInvariantLoad(AA))


    return !SawStore && !hasVolatileMemoryRef();

  return true;
}
