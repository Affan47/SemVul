visitUDiv(BinaryOperator &I) {
  Value *Op0 = I.getOperand(0), *Op1 = I.getOperand(1);

  if (Value *V = SimplifyVectorOp(I))
    return ReplaceInstUsesWith(I, V);

  if (Value *V = SimplifyUDivInst(Op0, Op1, DL, TLI, DT, AC))
    return ReplaceInstUsesWith(I, V);


  if (Instruction *Common = commonIDivTransforms(I))
    return Common;


  {
    Value *X;
    const APInt *C1, *C2;
    if (match(Op0, m_LShr(m_Value(X), m_APInt(C1))) &&
        match(Op1, m_APInt(C2))) {
      bool Overflow;
      APInt C2ShlC1 = C2->ushl_ov(*C1, Overflow);
      if (!Overflow) {
        bool IsExact = I.isExact() && match(Op0, m_Exact(m_Value()));
        BinaryOperator *BO = BinaryOperator::CreateUDiv(
            X, ConstantInt::get(X->getType(), C2ShlC1));
        if (IsExact)
          BO->setIsExact();
        return BO;
      }
    }
  }


  if (ZExtInst *ZOp0 = dyn_cast<ZExtInst>(Op0))
    if (Value *ZOp1 = dyn_castZExtVal(Op1, ZOp0->getSrcTy()))
      return new ZExtInst(
          Builder->CreateUDiv(ZOp0->getOperand(0), ZOp1, "div", I.isExact()),
          I.getType());


  SmallVector<UDivFoldAction, 6> UDivActions;
  if (visitUDivOperand(Op0, Op1, I, UDivActions))
    for (unsigned i = 0, e = UDivActions.size(); i != e; ++i) {
      FoldUDivOperandCb Action = UDivActions[i].FoldAction;
      Value *ActionOp1 = UDivActions[i].OperandToFold;
      Instruction *Inst;
      if (Action)
        Inst = Action(Op0, ActionOp1, I, *this);
      else {


        size_t SelectRHSIdx = i - 1;
        Value *SelectRHS = UDivActions[SelectRHSIdx].FoldResult;
        size_t SelectLHSIdx = UDivActions[i].SelectLHSIdx;
        Value *SelectLHS = UDivActions[SelectLHSIdx].FoldResult;
        Inst = SelectInst::Create(cast<SelectInst>(ActionOp1)->getCondition(),
                                  SelectLHS, SelectRHS);
      }


      if (e - i != 1) {
        Inst->insertBefore(&I);
        UDivActions[i].FoldResult = Inst;
      } else
        return Inst;
    }

  return nullptr;
}
