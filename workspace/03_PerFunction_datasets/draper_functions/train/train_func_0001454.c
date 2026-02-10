ConstantFoldInstruction(Instruction *I, const DataLayout &DL,
                                        const TargetLibraryInfo *TLI) {

  if (PHINode *PN = dyn_cast<PHINode>(I)) {
    Constant *CommonValue = nullptr;

    for (Value *Incoming : PN->incoming_values()) {


      if (isa<UndefValue>(Incoming))
        continue;

      Constant *C = dyn_cast<Constant>(Incoming);
      if (!C)
        return nullptr;

      if (ConstantExpr *NewC = dyn_cast<ConstantExpr>(C))
        C = ConstantFoldConstantExpression(NewC, DL, TLI);


      if (CommonValue && C != CommonValue)
        return nullptr;
      CommonValue = C;
    }


    return CommonValue ? CommonValue : UndefValue::get(PN->getType());
  }


  SmallVector<Constant*, 8> Ops;
  for (User::op_iterator i = I->op_begin(), e = I->op_end(); i != e; ++i) {
    Constant *Op = dyn_cast<Constant>(*i);
    if (!Op)
      return nullptr;


    if (ConstantExpr *NewCE = dyn_cast<ConstantExpr>(Op))
      Op = ConstantFoldConstantExpression(NewCE, DL, TLI);

    Ops.push_back(Op);
  }

  if (const CmpInst *CI = dyn_cast<CmpInst>(I))
    return ConstantFoldCompareInstOperands(CI->getPredicate(), Ops[0], Ops[1],
                                           DL, TLI);

  if (const LoadInst *LI = dyn_cast<LoadInst>(I))
    return ConstantFoldLoadInst(LI, DL);

  if (InsertValueInst *IVI = dyn_cast<InsertValueInst>(I)) {
    return ConstantExpr::getInsertValue(
                                cast<Constant>(IVI->getAggregateOperand()),
                                cast<Constant>(IVI->getInsertedValueOperand()),
                                IVI->getIndices());
  }

  if (ExtractValueInst *EVI = dyn_cast<ExtractValueInst>(I)) {
    return ConstantExpr::getExtractValue(
                                    cast<Constant>(EVI->getAggregateOperand()),
                                    EVI->getIndices());
  }

  return ConstantFoldInstOperands(I->getOpcode(), I->getType(), Ops, DL, TLI);
}
