create_expression(ExtractValueInst* E) {
  Expression e;

  e.varargs.push_back(lookup_or_add(E->getAggregateOperand()));
  for (ExtractValueInst::idx_iterator II = E->idx_begin(), IE = E->idx_end();
       II != IE; ++II)
    e.varargs.push_back(*II);
  e.function = 0;
  e.type = E->getType();
  e.opcode = Expression::EXTRACTVALUE;

  return e;
}
