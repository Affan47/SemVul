CollectAddOperandsWithScales(DenseMap<const SCEV *, APInt> &M,
                             SmallVector<const SCEV *, 8> &NewOps,
                             APInt &AccumulatedConstant,
                             const SCEV *const *Ops, size_t NumOperands,
                             const APInt &Scale,
                             ScalarEvolution &SE) {
  bool Interesting = false;


  unsigned i = 0;
  while (const SCEVConstant *C = dyn_cast<SCEVConstant>(Ops[i])) {
    ++i;

    if (Scale != 1 || AccumulatedConstant != 0 || C->getValue()->isZero())
      Interesting = true;
    AccumulatedConstant += Scale * C->getValue()->getValue();
  }


  for (; i != NumOperands; ++i) {
    const SCEVMulExpr *Mul = dyn_cast<SCEVMulExpr>(Ops[i]);
    if (Mul && isa<SCEVConstant>(Mul->getOperand(0))) {
      APInt NewScale =
        Scale * cast<SCEVConstant>(Mul->getOperand(0))->getValue()->getValue();
      if (Mul->getNumOperands() == 2 && isa<SCEVAddExpr>(Mul->getOperand(1))) {

        const SCEVAddExpr *Add = cast<SCEVAddExpr>(Mul->getOperand(1));
        Interesting |=
          CollectAddOperandsWithScales(M, NewOps, AccumulatedConstant,
                                       Add->op_begin(), Add->getNumOperands(),
                                       NewScale, SE);
      } else {


        SmallVector<const SCEV *, 4> MulOps(Mul->op_begin()+1, Mul->op_end());
        const SCEV *Key = SE.getMulExpr(MulOps);
        std::pair<DenseMap<const SCEV *, APInt>::iterator, bool> Pair =
          M.insert(std::make_pair(Key, NewScale));
        if (Pair.second) {
          NewOps.push_back(Pair.first->first);
        } else {
          Pair.first->second += NewScale;


          Interesting = true;
        }
      }
    } else {

      std::pair<DenseMap<const SCEV *, APInt>::iterator, bool> Pair =
        M.insert(std::make_pair(Ops[i], Scale));
      if (Pair.second) {
        NewOps.push_back(Pair.first->first);
      } else {
        Pair.first->second += Scale;


        Interesting = true;
      }
    }
  }

  return Interesting;
}
