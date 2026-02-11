applyOp(Value* operand)
{
  Boolean* op;
  bool bVal;

  op = Boolean::typeCheck(operand, showOp());
  bVal = op->getVal();
  return new Boolean(!bVal);
}
