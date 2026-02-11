isLegalToSwapOperand(
    GetElementPtrInst *FirstGEP, GetElementPtrInst *SecondGEP, Loop *CurLoop) {
  if (!FirstGEP || !FirstGEP->hasOneUse())
    return false;

  if (!SecondGEP || FirstGEP->getParent() != SecondGEP->getParent())
    return false;

  if (FirstGEP == SecondGEP)
    return false;

  unsigned FirstNum = FirstGEP->getNumOperands();
  unsigned SecondNum = SecondGEP->getNumOperands();

  if (FirstNum != SecondNum || FirstNum != 2)
    return false;

  Value *FirstBase = FirstGEP->getOperand(0);
  Value *SecondBase = SecondGEP->getOperand(0);
  Value *FirstOffset = FirstGEP->getOperand(1);

  if (CurLoop->isLoopInvariant(FirstOffset))
    return false;


  if (FirstBase->getType() != SecondBase->getType())
    return false;

  Instruction *FirstOffsetDef = dyn_cast<Instruction>(FirstOffset);


  if (FirstOffsetDef && FirstOffsetDef->isShift() &&
      dyn_cast<ConstantInt>(FirstOffsetDef->getOperand(1)))
    FirstOffsetDef = dyn_cast<Instruction>(FirstOffsetDef->getOperand(0));


  if (FirstOffsetDef)
    if (BinaryOperator *BO = dyn_cast<BinaryOperator>(FirstOffsetDef)) {
      unsigned opc = BO->getOpcode();
      if ((opc == Instruction::Add || opc == Instruction::Sub) &&
          (dyn_cast<ConstantInt>(BO->getOperand(0)) ||
           dyn_cast<ConstantInt>(BO->getOperand(1))))
        return false;
    }
  return true;
}
