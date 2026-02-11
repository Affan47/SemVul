copyIRFlags(const Value *V) {

  if (auto *OB = dyn_cast<OverflowingBinaryOperator>(V)) {
    setHasNoSignedWrap(OB->hasNoSignedWrap());
    setHasNoUnsignedWrap(OB->hasNoUnsignedWrap());
  }


  if (auto *PE = dyn_cast<PossiblyExactOperator>(V))
    setIsExact(PE->isExact());


  if (auto *FP = dyn_cast<FPMathOperator>(V))
    copyFastMathFlags(FP->getFastMathFlags());
}
