isSimpleEnoughValueToCommitHelper(Constant *C,
                                   SmallPtrSet<Constant*, 8> &SimpleConstants) {


  if (C->getNumOperands() == 0 || isa<BlockAddress>(C) ||
      isa<GlobalValue>(C))
    return true;


  if (isa<ConstantArray>(C) || isa<ConstantStruct>(C) ||
      isa<ConstantVector>(C)) {
    for (unsigned i = 0, e = C->getNumOperands(); i != e; ++i) {
      Constant *Op = cast<Constant>(C->getOperand(i));
      if (!isSimpleEnoughValueToCommit(Op, SimpleConstants))
        return false;
    }
    return true;
  }


  ConstantExpr *CE = cast<ConstantExpr>(C);
  switch (CE->getOpcode()) {
  case Instruction::BitCast:
  case Instruction::IntToPtr:
  case Instruction::PtrToInt:

    return isSimpleEnoughValueToCommit(CE->getOperand(0), SimpleConstants);


  case Instruction::GetElementPtr:
    for (unsigned i = 1, e = CE->getNumOperands(); i != e; ++i)
      if (!isa<ConstantInt>(CE->getOperand(i)))
        return false;
    return isSimpleEnoughValueToCommit(CE->getOperand(0), SimpleConstants);

  case Instruction::Add:

    if (!isa<ConstantInt>(CE->getOperand(1)))
      return false;
    return isSimpleEnoughValueToCommit(CE->getOperand(0), SimpleConstants);
  }
  return false;
}
