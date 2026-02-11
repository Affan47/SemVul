getMergedGlobalExpr(const Value *V) {
  const ConstantExpr *CE = dyn_cast_or_null<ConstantExpr>(V);
  if (!CE || CE->getNumOperands() != 3 ||
      CE->getOpcode() != Instruction::GetElementPtr)
    return nullptr;


  Value *Ptr = CE->getOperand(0);
  if (!isa<GlobalValue>(Ptr) ||
      !isa<StructType>(cast<PointerType>(Ptr->getType())->getElementType()))
    return nullptr;


  const ConstantInt *CI = dyn_cast_or_null<ConstantInt>(CE->getOperand(1));
  if (!CI || !CI->isZero())
    return nullptr;


  if (!isa<ConstantInt>(CE->getOperand(2)))
    return nullptr;

  return CE;
}
