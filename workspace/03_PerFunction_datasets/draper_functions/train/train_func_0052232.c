findBoundsGT(CoefficientInfo *A,
                                      CoefficientInfo *B,
                                      BoundInfo *Bound,
                                      unsigned K) const {
  Bound[K].Lower[Dependence::DVEntry::GT] = nullptr;
  Bound[K].Upper[Dependence::DVEntry::GT] = nullptr;
  if (Bound[K].Iterations) {
    const SCEV *Iter_1 = SE->getMinusSCEV(
        Bound[K].Iterations, SE->getOne(Bound[K].Iterations->getType()));
    const SCEV *NegPart =
      getNegativePart(SE->getMinusSCEV(A[K].Coeff, B[K].PosPart));
    Bound[K].Lower[Dependence::DVEntry::GT] =
      SE->getAddExpr(SE->getMulExpr(NegPart, Iter_1), A[K].Coeff);
    const SCEV *PosPart =
      getPositivePart(SE->getMinusSCEV(A[K].Coeff, B[K].NegPart));
    Bound[K].Upper[Dependence::DVEntry::GT] =
      SE->getAddExpr(SE->getMulExpr(PosPart, Iter_1), A[K].Coeff);
  }
  else {


    const SCEV *NegPart = getNegativePart(SE->getMinusSCEV(A[K].Coeff, B[K].PosPart));
    if (NegPart->isZero())
      Bound[K].Lower[Dependence::DVEntry::GT] = A[K].Coeff;
    const SCEV *PosPart = getPositivePart(SE->getMinusSCEV(A[K].Coeff, B[K].NegPart));
    if (PosPart->isZero())
      Bound[K].Upper[Dependence::DVEntry::GT] = A[K].Coeff;
  }
}
