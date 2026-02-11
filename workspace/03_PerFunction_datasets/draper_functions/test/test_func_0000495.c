dyn_castNotVal(Value *V) {


  if (BinaryOperator::isNot(V)) {
    Value *Operand = BinaryOperator::getNotArgument(V);
    if (!IsFreeToInvert(Operand, Operand->hasOneUse()))
      return Operand;
  }


  if (ConstantInt *C = dyn_cast<ConstantInt>(V))
    return ConstantInt::get(C->getType(), ~C->getValue());
  return nullptr;
}
