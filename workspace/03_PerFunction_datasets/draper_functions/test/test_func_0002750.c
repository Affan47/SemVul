FoldSelectOpOp(SelectInst &SI, Instruction *TI,
                                          Instruction *FI) {
  if (TI->getNumOperands() == 1) {


    if (TI->isCast()) {
      if (TI->getOperand(0)->getType() != FI->getOperand(0)->getType())
        return 0;
    } else {
      return 0;
    }


    Value *NewSI = Builder->CreateSelect(SI.getCondition(), TI->getOperand(0),
                                         FI->getOperand(0), SI.getName()+".v");
    return CastInst::Create(Instruction::CastOps(TI->getOpcode()), NewSI,
                            TI->getType());
  }


  if (!isa<BinaryOperator>(TI))
    return 0;


  Value *MatchOp, *OtherOpT, *OtherOpF;
  bool MatchIsOpZero;
  if (TI->getOperand(0) == FI->getOperand(0)) {
    MatchOp  = TI->getOperand(0);
    OtherOpT = TI->getOperand(1);
    OtherOpF = FI->getOperand(1);
    MatchIsOpZero = true;
  } else if (TI->getOperand(1) == FI->getOperand(1)) {
    MatchOp  = TI->getOperand(1);
    OtherOpT = TI->getOperand(0);
    OtherOpF = FI->getOperand(0);
    MatchIsOpZero = false;
  } else if (!TI->isCommutative()) {
    return 0;
  } else if (TI->getOperand(0) == FI->getOperand(1)) {
    MatchOp  = TI->getOperand(0);
    OtherOpT = TI->getOperand(1);
    OtherOpF = FI->getOperand(0);
    MatchIsOpZero = true;
  } else if (TI->getOperand(1) == FI->getOperand(0)) {
    MatchOp  = TI->getOperand(1);
    OtherOpT = TI->getOperand(0);
    OtherOpF = FI->getOperand(1);
    MatchIsOpZero = true;
  } else {
    return 0;
  }


  Value *NewSI = Builder->CreateSelect(SI.getCondition(), OtherOpT,
                                       OtherOpF, SI.getName()+".v");

  if (BinaryOperator *BO = dyn_cast<BinaryOperator>(TI)) {
    if (MatchIsOpZero)
      return BinaryOperator::Create(BO->getOpcode(), MatchOp, NewSI);
    else
      return BinaryOperator::Create(BO->getOpcode(), NewSI, MatchOp);
  }
  llvm_unreachable("Shouldn't get here");
  return 0;
}
