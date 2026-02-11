create_expression(GetElementPtrInst* G) {
  Expression e;

  e.varargs.push_back(lookup_or_add(G->getPointerOperand()));
  e.function = 0;
  e.type = G->getType();
  e.opcode = Expression::GEP;

  for (GetElementPtrInst::op_iterator I = G->idx_begin(), E = G->idx_end();
       I != E; ++I)
    e.varargs.push_back(lookup_or_add(*I));

  return e;
}
