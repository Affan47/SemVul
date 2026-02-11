un_index_lits_all(struct clause *c)
{
  struct literal *lit;

  lit = c->first_lit;
  while (lit != NULL) {
    if (lit->atom->varnum == ANSWER)
      ;
    else if (lit->sign) {
      if (Flags[NO_FAPL].val == 0)
	fpa_delete(lit->atom, Parms[FPA_LITERALS].val, Fpa_pos_lits);
      if ((Flags[FOR_SUB_FPA].val == 0 && Flags[FOR_SUB].val) ||
	  (Flags[UNIT_DELETION].val && num_literals(c) == 1))
	is_delete(lit->atom, Is_pos_lits);
    }
    else {
      if (Flags[NO_FANL].val == 0)
	fpa_delete(lit->atom, Parms[FPA_LITERALS].val, Fpa_neg_lits);
      if ((Flags[FOR_SUB_FPA].val == 0 && Flags[FOR_SUB].val) ||
	  (Flags[UNIT_DELETION].val && num_literals(c) == 1))
	is_delete(lit->atom, Is_neg_lits);
    }
    lit = lit->next_lit;
  }
}
