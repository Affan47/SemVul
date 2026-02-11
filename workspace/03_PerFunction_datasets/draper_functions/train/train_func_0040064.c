findBoundsLT(CoefficientInfo *A,
                                      CoefficientInfo *B,
                                      BoundInfo *Bound,
                                      unsigned K) const {
  Bound[K].Lower[Dependence::DVEntry::LT] = nullptr;
  Bound[K].Upper[Dependence::DVEntry::LT] = nullptr;
  if (Bound[K].Iterations) {
    const SCEV *Iter_1 = SE->getMinusSCEV(
        Bound[K].Iterations, SE->getOne(Bound[K].Iterations->getType()));
    const SCEV *NegPart =
      getNegativePart(SE->getMinusSCEV(A[K].NegPart, B[K].Coeff));
    Bound[K].Lower[Dependence::DVEntry::LT] =
      SE->getMinusSCEV(SE->getMulExpr(NegPart, Iter_1), B[K].Coeff);
    const SCEV *PosPart =
      getPositivePart(SE->getMinusSCEV(A[K].PosPart, B[K].Coeff));
    Bound[K].Upper[Dependence::DVEntry::LT] =
      SE->getMinusSCEV(SE->getMulExpr(PosPart, Iter_1), B[K].Coeff);
  }
  else {


    const SCEV *NegPart =
      getNegativePart(SE->getMinusSCEV(A[K].NegPart, B[K].Coeff));
    if (NegPart->isZero())
      Bound[K].Lower[Dependence::DVEntry::LT] = SE->getNegativeSCEV(B[K].Coeff);
    const SCEV *PosPart =
      getPositivePart(SE->getMinusSCEV(A[K].PosPart, B[K].Coeff));
    if (PosPart->isZero())
      Bound[K].Upper[Dependence::DVEntry::LT] = SE->getNegativeSCEV(B[K].Coeff);
  }
}
