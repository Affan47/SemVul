create_expression(InsertElementInst* I) {
  Expression e;

  e.varargs.push_back(lookup_or_add(I->getOperand(0)));
  e.varargs.push_back(lookup_or_add(I->getOperand(1)));
  e.varargs.push_back(lookup_or_add(I->getOperand(2)));
  e.function = 0;
  e.type = I->getType();
  e.opcode = Expression::INSERT;

  return e;
}
