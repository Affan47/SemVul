str_to_sn(char *str,
	      int arity)
{
  struct sym_ent *p, *save;
  int i;
  long dummy;

  save = NULL;
  for (i = 0; i < SYM_TAB_SIZE; i++) {
    p = Sym_tab[i];
    while (p != NULL) {
      if (!str_ident(str, p->name))
	p = p->next;
      else if (p->arity != arity) {
	save = p;
	p = p->next;
      }
      else {
	if (p->eval_code != 0)

	  Internal_flags[DOLLAR_PRESENT] = 1;
	return(p->sym_num);
      }
    }
  }

  if (save && !save->special_op &&
      Flags[CHECK_ARITY].val &&
      Internal_flags[REALLY_CHECK_ARITY] &&
      !str_ident(str, "$Quantified") &&
      !str_ident(str, "$Hyps") &&
      !str_ident(str, "$Concs")    ) {

    fprintf(stderr, "%c\n\nWARNING, multiple arity: %s/%d, %s/%d.\n\n", Bell,
	    save->name, save->arity, str, arity);
  }


  p = insert_sym(str, arity);

  if (str[0] == '$' &&

      p->sym_num != Cons_sym_num &&
      p->sym_num != Nil_sym_num &&

      p->sym_num != Ignore_sym_num &&
      p->sym_num != Chr_sym_num &&
      p->sym_num != Dots_sym_num &&
      !initial_str("$Quantified", str) &&

      !initial_str("$ANS", str) &&
      !initial_str("$Ans", str) &&
      !initial_str("$ans", str) &&

      !initial_str("$Connect", str) &&

      !str_ident(str, "$NUCLEUS") &&
      !str_ident(str, "$BOTH") &&
      !str_ident(str, "$LINK") &&
      !str_ident(str, "$SATELLITE") &&

      !str_ident(str, "$FSUB") &&
      !str_ident(str, "$BSUB") &&
      !str_ident(str, "$EQUIV") &&

      !str_ident(str, "$Concs") &&
      !str_ident(str, "$Hyps") &&

      !skolem_symbol(p->sym_num) &&
      !str_long(str+1, &dummy))

    fprintf(stderr, "%c\n\nWARNING, unrecognized $ symbol: %s.\n\n", Bell, str);

  return(p->sym_num);

}
