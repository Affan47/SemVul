SimplifyBSwap(BinaryOperator &I) {
  IntegerType *ITy = dyn_cast<IntegerType>(I.getType());


  if (I.getType()->isVectorTy()) return nullptr;


  unsigned Op = I.getOpcode();
  if (Op != Instruction::And && Op != Instruction::Or &&
      Op != Instruction::Xor)
    return nullptr;

  Value *OldLHS = I.getOperand(0);
  Value *OldRHS = I.getOperand(1);
  ConstantInt *ConstLHS = dyn_cast<ConstantInt>(OldLHS);
  ConstantInt *ConstRHS = dyn_cast<ConstantInt>(OldRHS);
  IntrinsicInst *IntrLHS = dyn_cast<IntrinsicInst>(OldLHS);
  IntrinsicInst *IntrRHS = dyn_cast<IntrinsicInst>(OldRHS);
  bool IsBswapLHS = (IntrLHS && IntrLHS->getIntrinsicID() == Intrinsic::bswap);
  bool IsBswapRHS = (IntrRHS && IntrRHS->getIntrinsicID() == Intrinsic::bswap);

  if (!IsBswapLHS && !IsBswapRHS)
    return nullptr;

  if (!IsBswapLHS && !ConstLHS)
    return nullptr;

  if (!IsBswapRHS && !ConstRHS)
    return nullptr;


  Value *NewLHS = IsBswapLHS ? IntrLHS->getOperand(0) :
                  Builder->getInt(ConstLHS->getValue().byteSwap());

  Value *NewRHS = IsBswapRHS ? IntrRHS->getOperand(0) :
                  Builder->getInt(ConstRHS->getValue().byteSwap());

  Value *BinOp = nullptr;
  if (Op == Instruction::And)
    BinOp = Builder->CreateAnd(NewLHS, NewRHS);
  else if (Op == Instruction::Or)
    BinOp = Builder->CreateOr(NewLHS, NewRHS);
  else
    BinOp = Builder->CreateXor(NewLHS, NewRHS);

  Module *M = I.getParent()->getParent()->getParent();
  Function *F = Intrinsic::getDeclaration(M, Intrinsic::bswap, ITy);
  return Builder->CreateCall(F, BinOp);
}
