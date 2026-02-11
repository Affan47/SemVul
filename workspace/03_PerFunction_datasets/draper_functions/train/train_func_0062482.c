parm_handler(FILE *fout, Term t, BOOL echo, int unknown_action)
{
  char *name   = sn_to_str(SYMNUM(ARG(t,0)));
  Term tval  = ARG(t,1);

  int id = str_to_parm_id(name);
  if (id != -1) {
    int val;
    if (term_to_int(tval, &val))
      assign_parm(id, val, echo);
    else {
      execute_unknown_action(fout, unknown_action, t,
			     "Parm needs integer value");
    }
  }
  else {
    id = str_to_floatparm_id(name);
    if (id != -1) {
      double val;
      if (term_to_number(tval, &val))
	assign_floatparm(id, val, echo);
      else
	execute_unknown_action(fout, unknown_action, t,
			       "Floatparm needs integer or double value");
    }
    else {
      id = str_to_stringparm_id(name);
      if (id != -1) {
	if (CONSTANT(tval)) {
	  char *s = sn_to_str(SYMNUM(tval));
	  assign_stringparm(id, s, echo);
	}
	else
	  execute_unknown_action(fout, unknown_action, t,
				 "Stringparm needs constant value");
      }
      else
	execute_unknown_action(fout, unknown_action, t,
			       "Parameter not recognized");
    }
  }
}
