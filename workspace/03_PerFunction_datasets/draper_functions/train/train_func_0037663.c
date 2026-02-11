fold_denial(Topform c, int alpha_max)
{
  static BOOL done = FALSE;
  if (done || !neg_eq_unit(c->literals) || !ground_clause(c->literals))
    return NULL;
  else {

    Term alpha = ARG(c->literals->atom,0);
    Term beta =  ARG(c->literals->atom,1);

    if (!CONSTANT(beta) &&
	(alpha_max == -1 || symbol_count(alpha) <= alpha_max)) {
      int new_constant_sn = fresh_symbol("c_", 0);
      Topform ca = clause_with_new_constant(c, alpha, new_constant_sn);
      new_constant_properties(new_constant_sn);
      done = TRUE;
      return ca;
    }
    else
      return NULL;
  }
}
