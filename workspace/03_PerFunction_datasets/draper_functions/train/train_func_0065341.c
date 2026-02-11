visitFRem(BinaryOperator &I) {
  Value *Op0 = I.getOperand(0), *Op1 = I.getOperand(1);

  if (Value *V = SimplifyVectorOp(I))
    return ReplaceInstUsesWith(I, V);

  if (Value *V = SimplifyFRemInst(Op0, Op1, I.getFastMathFlags(),
                                  DL, TLI, DT, AC))
    return ReplaceInstUsesWith(I, V);


  if (isa<SelectInst>(Op1) && SimplifyDivRemOfSelect(I))
    return &I;

  return nullptr;
}
