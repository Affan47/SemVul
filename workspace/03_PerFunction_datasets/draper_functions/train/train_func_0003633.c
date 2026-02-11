interp_term(void)
{
  Symbol_data s;

  Term symlist = get_nil_term();

  for (s = Symbols; s != NULL; s = s->next) {
    if (s->attribute != EQUALITY_SYMBOL) {
      int i, n;
      Term entry, symterm, tableterm;
      symterm = get_rigid_term_dangerously(s->sn, s->arity);
      for (i = 0; i < s->arity; i++)
	ARG(symterm,i) = get_variable_term(i);
      n = int_power(Domain_size, s->arity);
      tableterm = get_nil_term();
      for (i = n-1; i >= 0; i--) {
	int id = s->base + i;
	Term it;
	if (Cells[id].value == NULL)
	  fatal_error("interp_term, incomplete interpretation");
	it = nat_to_term(VARNUM(Cells[id].value));
	tableterm = listterm_cons(it, tableterm);
      }
      entry = build_binary_term(str_to_sn(s->type == FUNCTION ? "function" : "relation", 2),
				symterm, tableterm);
      symlist = listterm_cons(entry, symlist);
    }
  }
  return build_binary_term(str_to_sn("interpretation", 2),
			   nat_to_term(Domain_size),
			   symlist);
}
