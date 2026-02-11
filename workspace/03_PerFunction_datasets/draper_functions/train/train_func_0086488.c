DoInitialMatch(const SCEV *S, Loop *L,
                           SmallVectorImpl<const SCEV *> &Good,
                           SmallVectorImpl<const SCEV *> &Bad,
                           ScalarEvolution &SE) {

  if (SE.properlyDominates(S, L->getHeader())) {
    Good.push_back(S);
    return;
  }


  if (const SCEVAddExpr *Add = dyn_cast<SCEVAddExpr>(S)) {
    for (SCEVAddExpr::op_iterator I = Add->op_begin(), E = Add->op_end();
         I != E; ++I)
      DoInitialMatch(*I, L, Good, Bad, SE);
    return;
  }


  if (const SCEVAddRecExpr *AR = dyn_cast<SCEVAddRecExpr>(S))
    if (!AR->getStart()->isZero()) {
      DoInitialMatch(AR->getStart(), L, Good, Bad, SE);
      DoInitialMatch(SE.getAddRecExpr(SE.getConstant(AR->getType(), 0),
                                      AR->getStepRecurrence(SE),

                                      AR->getLoop(), SCEV::FlagAnyWrap),
                     L, Good, Bad, SE);
      return;
    }


  if (const SCEVMulExpr *Mul = dyn_cast<SCEVMulExpr>(S))
    if (Mul->getOperand(0)->isAllOnesValue()) {
      SmallVector<const SCEV *, 4> Ops(Mul->op_begin()+1, Mul->op_end());
      const SCEV *NewMul = SE.getMulExpr(Ops);

      SmallVector<const SCEV *, 4> MyGood;
      SmallVector<const SCEV *, 4> MyBad;
      DoInitialMatch(NewMul, L, MyGood, MyBad, SE);
      const SCEV *NegOne = SE.getSCEV(ConstantInt::getAllOnesValue(
        SE.getEffectiveSCEVType(NewMul->getType())));
      for (SmallVectorImpl<const SCEV *>::const_iterator I = MyGood.begin(),
           E = MyGood.end(); I != E; ++I)
        Good.push_back(SE.getMulExpr(NegOne, *I));
      for (SmallVectorImpl<const SCEV *>::const_iterator I = MyBad.begin(),
           E = MyBad.end(); I != E; ++I)
        Bad.push_back(SE.getMulExpr(NegOne, *I));
      return;
    }


  Bad.push_back(S);
}
