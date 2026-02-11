HowFarToNonZero(const SCEV *V, const Loop *L) {


  if (const SCEVConstant *C = dyn_cast<SCEVConstant>(V)) {
    if (!C->getValue()->isNullValue())
      return getConstant(C->getType(), 0);
    return getCouldNotCompute();
  }


  return getCouldNotCompute();
}
