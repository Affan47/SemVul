isNonEscapingLocalObject(const Value *V) {

  if (isa<AllocaInst>(V) || isNoAliasCall(V))


    return !PointerMayBeCaptured(V, false, true);


  if (const Argument *A = dyn_cast<Argument>(V))
    if (A->hasByValAttr() || A->hasNoAliasAttr()) {

      if (A->hasNoCaptureAttr())
        return true;
      return !PointerMayBeCaptured(V, false, true);
    }
  return false;
}
