gen_paramlist(CGState *cgs, ExpListNode *eln, int nparams) {
  Value *v;
  if(!eln) return 0;
  if(eln->next)
    nparams = gen_paramlist(cgs, eln->next, nparams + 4);
  v = gen_exp(cgs, eln->exp);
  gen_unop(cgs, OP_PUSH, gen_value(v));
  free_reg(cgs, v);
  return nparams;
}
