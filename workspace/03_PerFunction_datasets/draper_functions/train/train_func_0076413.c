visitBinaryOperator(BinaryOperator &I) {
    Value *LHS = I.getOperand(0), *RHS = I.getOperand(1);
    if (!isa<Constant>(LHS))
      if (Constant *SimpleLHS = SimplifiedValues.lookup(LHS))
        LHS = SimpleLHS;
    if (!isa<Constant>(RHS))
      if (Constant *SimpleRHS = SimplifiedValues.lookup(RHS))
        RHS = SimpleRHS;

    Value *SimpleV = nullptr;
    const DataLayout &DL = I.getModule()->getDataLayout();
    if (auto FI = dyn_cast<FPMathOperator>(&I))
      SimpleV =
          SimplifyFPBinOp(I.getOpcode(), LHS, RHS, FI->getFastMathFlags(), DL);
    else
      SimpleV = SimplifyBinOp(I.getOpcode(), LHS, RHS, DL);

    if (Constant *C = dyn_cast_or_null<Constant>(SimpleV))
      SimplifiedValues[&I] = C;

    if (SimpleV)
      return true;
    return Base::visitBinaryOperator(I);
  }
