process_demod_formulas(Plist formulas, BOOL echo)
{
  Plist new = NULL;
  Plist p;

  for (p = formulas; p; p = p->next) {
    Topform tf = p->v;
    if (clausal_formula(tf->formula)) {

      tf->literals = formula_to_literals(tf->formula);
      upward_clause_links(tf);
      zap_formula(tf->formula);
      tf->formula = NULL;
      tf->is_formula = FALSE;
      clause_set_variables(tf, MAX_VARS);
      new = plist_prepend(new, tf);
    }
    else if (tf->formula->type == IMP_FORM ||
	     tf->formula->type == IMPBY_FORM ||
	     tf->formula->type == IFF_FORM) {
       new = plist_prepend(new, tf);
    }
    else
      fatal_error("process_demod_formulas: bad demodulator");
  }
  zap_plist(formulas);
  new = reverse_plist(new);
  return new;
}
