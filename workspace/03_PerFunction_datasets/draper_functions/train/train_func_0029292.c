SimplifyShift(unsigned Opcode, Value *Op0, Value *Op1,
                            const Query &Q, unsigned MaxRecurse) {
  if (Constant *C0 = dyn_cast<Constant>(Op0)) {
    if (Constant *C1 = dyn_cast<Constant>(Op1)) {
      Constant *Ops[] = { C0, C1 };
      return ConstantFoldInstOperands(Opcode, C0->getType(), Ops, Q.DL, Q.TLI);
    }
  }


  if (match(Op0, m_Zero()))
    return Op0;


  if (match(Op1, m_Zero()))
    return Op0;


  if (isUndefShift(Op1))
    return UndefValue::get(Op0->getType());


  if (isa<SelectInst>(Op0) || isa<SelectInst>(Op1))
    if (Value *V = ThreadBinOpOverSelect(Opcode, Op0, Op1, Q, MaxRecurse))
      return V;


  if (isa<PHINode>(Op0) || isa<PHINode>(Op1))
    if (Value *V = ThreadBinOpOverPHI(Opcode, Op0, Op1, Q, MaxRecurse))
      return V;

  return nullptr;
}
