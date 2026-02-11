GetBaseValue(const SCEV *S) {
  if (const SCEVAddRecExpr *AR = dyn_cast<SCEVAddRecExpr>(S)) {


    return GetBaseValue(AR->getStart());
  } else if (const SCEVAddExpr *A = dyn_cast<SCEVAddExpr>(S)) {

    const SCEV *Last = A->getOperand(A->getNumOperands()-1);
    if (Last->getType()->isPointerTy())
      return GetBaseValue(Last);
  } else if (const SCEVUnknown *U = dyn_cast<SCEVUnknown>(S)) {

    return U->getValue();
  }

  return 0;
}
