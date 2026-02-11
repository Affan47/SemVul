do_if(gpasmVal r,
		      char *name,
		      int arity,
		      struct pnode *parms)
{
  struct pnode *p;
  state.lst.line.linetype = dir;
  enter_if();


  if (state.astack->prev_enabled) {
    if (enforce_arity(arity, 1)) {
      p = HEAD(parms);
      state.astack->enabled = maybe_evaluate(p);
    }
  }

  return r;
}
