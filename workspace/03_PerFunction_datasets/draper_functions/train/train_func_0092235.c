do_org(gpasmVal r,
		       char *name,
		       int arity,
		       struct pnode *parms)
{
  struct pnode *p;

  state.lst.line.linetype = org;

  if (enforce_arity(arity, 1)) {
    p = HEAD(parms);
    if (can_evaluate(p)) {
      gpasmVal new_org = evaluate(p);
      if (_16bit_core && (new_org & 0x1))
        gperror(GPE_ORG_ODD, NULL);
      r = new_org >> _16bit_core;
      if (state.mode == absolute) {
        state.org = r;
      }	else {


        snprintf(state.obj.new_sec_name,
                 sizeof(state.obj.new_sec_name),
                 ".org_%x",
                 r);
        state.obj.new_sec_addr = r;
        state.obj.new_sec_flags = STYP_TEXT | STYP_ABS;
        state.lst.line.linetype = sec;
        state.next_state = state_section;
      }
    }
		else
		  r = 0;
  }

  return r;
}
