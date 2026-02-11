MACE_collect_symbols(struct term *t,
				 int type)
{
  if (t->type == VARIABLE || domain_element(t))
    return;
  else {
    char *name = sn_to_str(t->sym_num);
    int arity = sn_to_arity(t->sym_num) + (type == FUNCTION ? 1 : 0);
    int id = str_to_id(name);
    struct rel *r;

    if (id != -1) {

      struct symbol *s = Symbols + id;
      if (s->arity != arity)
	abend("MACE_collect_symbols, multiple arity");
    }
    else {

      int j;
      char arg_types[MAX_ARITY][MAX_MNAME];
      struct symbol *s;

      if (arity > MAX_ARITY)
	MACE_abend("arity too great");

      for (j = 0; j < arity; j++)
	strcpy(arg_types[j], "univ");

      id = declare_symbol_sorted(name, arity, arg_types);
      s = Symbols + id;

      s->type = type;
      if (type == RELATION) {
	if (is_eq(t->sym_num))
	  SET_BIT(s->properties, MACE_EQ_BIT);
	else if (t->sym_num == str_to_sn("<", 2))
	  SET_BIT(s->properties, MACE_ORDER_BIT);
      }
    }
    for (r = t->farg; r; r = r->narg)
      MACE_collect_symbols(r->argval, FUNCTION);
  }
}
