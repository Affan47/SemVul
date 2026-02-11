visitSwitchInst(SwitchInst &I) {
  ExecutionContext &SF = ECStack.back();
  Value* Cond = I.getCondition();
  Type *ElTy = Cond->getType();
  GenericValue CondVal = getOperandValue(Cond, SF);


  BasicBlock *Dest = 0;
  unsigned NumCases = I.getNumCases();

  for (unsigned i = 1; i < NumCases; ++i) {
    GenericValue CaseVal = getOperandValue(I.getCaseValue(i), SF);
    if (executeICMP_EQ(CondVal, CaseVal, ElTy).IntVal != 0) {
      Dest = cast<BasicBlock>(I.getSuccessor(i));
      break;
    }
  }
  if (!Dest) Dest = I.getDefaultDest();
  SwitchToNewBasicBlock(Dest, SF);
}
