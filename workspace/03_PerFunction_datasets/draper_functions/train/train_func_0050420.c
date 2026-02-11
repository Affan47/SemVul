clause_weight(Literals lits)
{
  double wt;

  if (!Not_rules && !Or_rules) {


    Literals lit;
    wt = 0;
    for (lit = lits; lit; lit = lit->next) {
      Context subst = get_context();
      wt += weight(lit->atom, subst);
      free_context(subst);
    }
    wt += (negative_literals(lits) * Not_weight);
    wt += ((number_of_literals(lits)-1) * Or_weight);
  }
  else {


    Term temp = lits_to_term(lits);
    Context subst = get_context();
    wt = weight(temp, subst);
    free_context(subst);
    free_lits_to_term(temp);


    if (!Not_rules)
      wt += (negative_literals(lits) * (Not_weight - 1));
    if (!Or_rules)
      wt += ((number_of_literals(lits) - 1) * (Or_weight - 1));
  }

  if (Depth_penalty != 0)
    wt += Depth_penalty * literals_depth(lits);

  if (Var_penalty != 0)
    wt += Var_penalty * number_of_variables(lits);

  if (Complexity != 0)
    wt += Complexity * (1 - clause_complexity(lits, 4, 0));

  return wt;

}
