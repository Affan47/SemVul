isNonConstantNegative(const SCEV *F) {
  const SCEVMulExpr *Mul = dyn_cast<SCEVMulExpr>(F);
  if (!Mul) return false;


  const SCEVConstant *SC = dyn_cast<SCEVConstant>(Mul->getOperand(0));
  if (!SC) return false;


  return SC->getValue()->getValue().isNegative();
}
