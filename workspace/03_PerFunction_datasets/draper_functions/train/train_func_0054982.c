remapConstantExpr(Module *M, Function *F, ConstantExpr *C,
                                        IRBuilder<> &Builder) {
  bool OperandChanged = false;
  SmallVector<Value *, 4> NewOperands;
  unsigned NumOperands = C->getNumOperands();


  for (unsigned i = 0; i < NumOperands; ++i) {
    Value *Operand = C->getOperand(i);
    Value *NewOperand = remapConstant(M, F, cast<Constant>(Operand), Builder);
    OperandChanged |= Operand != NewOperand;
    NewOperands.push_back(NewOperand);
  }


  if (!OperandChanged) {
    return C;
  }


  unsigned Opcode = C->getOpcode();
  switch (Opcode) {
  case Instruction::ICmp:

    return Builder.CreateICmp(CmpInst::Predicate(C->getPredicate()),
                              NewOperands[0], NewOperands[1]);
  case Instruction::FCmp:

    llvm_unreachable("Address space conversion should have no effect "
                     "on float point CompareConstantExpr (fcmp)!");
  case Instruction::ExtractElement:

    return Builder.CreateExtractElement(NewOperands[0], NewOperands[1]);
  case Instruction::InsertElement:

    return Builder.CreateInsertElement(NewOperands[0], NewOperands[1],
                                       NewOperands[2]);
  case Instruction::ShuffleVector:

    return Builder.CreateShuffleVector(NewOperands[0], NewOperands[1],
                                       NewOperands[2]);
  case Instruction::ExtractValue:

    return Builder.CreateExtractValue(NewOperands[0], C->getIndices());
  case Instruction::InsertValue:

    return Builder.CreateInsertValue(NewOperands[0], NewOperands[1],
                                     C->getIndices());
  case Instruction::GetElementPtr:

    return cast<GEPOperator>(C)->isInBounds()
               ? Builder.CreateGEP(
                     cast<GEPOperator>(C)->getSourceElementType(),
                     NewOperands[0],
                     makeArrayRef(&NewOperands[1], NumOperands - 1))
               : Builder.CreateInBoundsGEP(
                     cast<GEPOperator>(C)->getSourceElementType(),
                     NewOperands[0],
                     makeArrayRef(&NewOperands[1], NumOperands - 1));
  case Instruction::Select:

    return Builder.CreateSelect(NewOperands[0], NewOperands[1], NewOperands[2]);
  default:

    if (Instruction::isBinaryOp(Opcode)) {
      return Builder.CreateBinOp(Instruction::BinaryOps(C->getOpcode()),
                                 NewOperands[0], NewOperands[1]);
    }

    if (Instruction::isCast(Opcode)) {
      return Builder.CreateCast(Instruction::CastOps(C->getOpcode()),
                                NewOperands[0], C->getType());
    }
    llvm_unreachable("GenericToNVVM encountered an unsupported ConstantExpr");
  }
}
