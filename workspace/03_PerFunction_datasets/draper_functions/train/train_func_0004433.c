IsConstantOffsetFromGlobal(Constant *C, GlobalValue *&GV,
                                       APInt &Offset, const DataLayout &DL) {

  if ((GV = dyn_cast<GlobalValue>(C))) {
    unsigned BitWidth = DL.getPointerTypeSizeInBits(GV->getType());
    Offset = APInt(BitWidth, 0);
    return true;
  }


  ConstantExpr *CE = dyn_cast<ConstantExpr>(C);
  if (!CE) return false;


  if (CE->getOpcode() == Instruction::PtrToInt ||
      CE->getOpcode() == Instruction::BitCast)
    return IsConstantOffsetFromGlobal(CE->getOperand(0), GV, Offset, DL);


  GEPOperator *GEP = dyn_cast<GEPOperator>(CE);
  if (!GEP)
    return false;

  unsigned BitWidth = DL.getPointerTypeSizeInBits(GEP->getType());
  APInt TmpOffset(BitWidth, 0);


  if (!IsConstantOffsetFromGlobal(CE->getOperand(0), GV, TmpOffset, DL))
    return false;


  if (!GEP->accumulateConstantOffset(DL, TmpOffset))
    return false;

  Offset = TmpOffset;
  return true;
}
