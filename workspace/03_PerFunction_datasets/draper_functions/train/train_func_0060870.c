ConstantFoldInsertElementInstruction(Constant *Val,
                                                     Constant *Elt,
                                                     Constant *Idx) {
  ConstantInt *CIdx = dyn_cast<ConstantInt>(Idx);
  if (!CIdx) return 0;
  APInt idxVal = CIdx->getValue();
  if (isa<UndefValue>(Val)) {


    if (isa<UndefValue>(Elt))
      return Val;


    unsigned numOps =
      cast<VectorType>(Val->getType())->getNumElements();
    std::vector<Constant*> Ops;
    Ops.reserve(numOps);
    for (unsigned i = 0; i < numOps; ++i) {
      Constant *Op =
        (idxVal == i) ? Elt : UndefValue::get(Elt->getType());
      Ops.push_back(Op);
    }
    return ConstantVector::get(Ops);
  }
  if (isa<ConstantAggregateZero>(Val)) {


    if (Elt->isNullValue())
      return Val;


    unsigned numOps =
      cast<VectorType>(Val->getType())->getNumElements();
    std::vector<Constant*> Ops;
    Ops.reserve(numOps);
    for (unsigned i = 0; i < numOps; ++i) {
      Constant *Op =
        (idxVal == i) ? Elt : Constant::getNullValue(Elt->getType());
      Ops.push_back(Op);
    }
    return ConstantVector::get(Ops);
  }
  if (ConstantVector *CVal = dyn_cast<ConstantVector>(Val)) {

    std::vector<Constant*> Ops;
    Ops.reserve(CVal->getNumOperands());
    for (unsigned i = 0; i < CVal->getNumOperands(); ++i) {
      Constant *Op =
        (idxVal == i) ? Elt : cast<Constant>(CVal->getOperand(i));
      Ops.push_back(Op);
    }
    return ConstantVector::get(Ops);
  }

  return 0;
}
