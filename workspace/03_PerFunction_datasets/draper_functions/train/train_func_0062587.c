splitable_literal(struct clause *c,
		      struct literal *l)
{
  if (num_literals(c) < 2 || !ground(l->atom))
    return 0;
  else {
    int ok = 1;
    if (ok && Flags[SPLIT_POS].val)
      ok = pos_clause(c);
    if (ok && Flags[SPLIT_NEG].val)
      ok = neg_clause(c);
    if (ok && Flags[SPLIT_NONHORN].val)
      ok = l->sign && !horn_clause(c);
    return ok;
  }
}
