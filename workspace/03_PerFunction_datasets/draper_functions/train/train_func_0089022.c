SimplifyRem(Instruction::BinaryOps Opcode, Value *Op0, Value *Op1,
                          const TargetData *TD, const DominatorTree *DT,
                          unsigned MaxRecurse) {
  if (Constant *C0 = dyn_cast<Constant>(Op0)) {
    if (Constant *C1 = dyn_cast<Constant>(Op1)) {
      Constant *Ops[] = { C0, C1 };
      return ConstantFoldInstOperands(Opcode, C0->getType(), Ops, TD);
    }
  }


  if (match(Op1, m_Undef()))
    return Op1;


  if (match(Op0, m_Undef()))
    return Constant::getNullValue(Op0->getType());


  if (match(Op0, m_Zero()))
    return Op0;


  if (match(Op1, m_Zero()))
    return UndefValue::get(Op0->getType());


  if (match(Op1, m_One()))
    return Constant::getNullValue(Op0->getType());

  if (Op0->getType()->isIntegerTy(1))

    return Constant::getNullValue(Op0->getType());


  if (Op0 == Op1)
    return Constant::getNullValue(Op0->getType());


  if (isa<SelectInst>(Op0) || isa<SelectInst>(Op1))
    if (Value *V = ThreadBinOpOverSelect(Opcode, Op0, Op1, TD, DT, MaxRecurse))
      return V;


  if (isa<PHINode>(Op0) || isa<PHINode>(Op1))
    if (Value *V = ThreadBinOpOverPHI(Opcode, Op0, Op1, TD, DT, MaxRecurse))
      return V;

  return 0;
}
