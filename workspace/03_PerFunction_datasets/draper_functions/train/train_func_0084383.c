createAndInstr(Instruction *InsertBefore, Value *Opnd,
                             const APInt &ConstOpnd) {
  if (ConstOpnd != 0) {
    if (!ConstOpnd.isAllOnesValue()) {
      LLVMContext &Ctx = Opnd->getType()->getContext();
      Instruction *I;
      I = BinaryOperator::CreateAnd(Opnd, ConstantInt::get(Ctx, ConstOpnd),
                                    "and.ra", InsertBefore);
      I->setDebugLoc(InsertBefore->getDebugLoc());
      return I;
    }
    return Opnd;
  }
  return nullptr;
}
