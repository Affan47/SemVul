do_extern(gpasmVal r,
		          char *name,
		          int arity,
		          struct pnode *parms)
{
  char *p;
  state.lst.line.linetype = dir;

  if (state.mode == absolute) {
    gperror(GPE_OBJECT_ONLY, NULL);
  } else {
    for (; parms; parms = TAIL(parms)) {
      p = maybe_evaluate_concat(HEAD(parms));
      if (p) {
        set_global(p, 0, PERMANENT, gvt_extern);
      }
    }
  }

  return r;
}
