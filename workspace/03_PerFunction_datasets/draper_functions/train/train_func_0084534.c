init_white_black(Plist white, Plist black)
{
  Plist p;
  for (p = white; p; p = p->next) {
    Clause_eval ce = compile_clause_eval_rule(p->v);
    if (ce == NULL)
      fatal_error("Error in \"keep\" rule");
    else {
      White_rules = plist_append(White_rules, ce);
      if (rule_contains_semantics(ce))
	Rule_needs_semantics = TRUE;
    }
  }
  for (p = black; p; p = p->next) {
    Clause_eval ce = compile_clause_eval_rule(p->v);
    if (ce == NULL)
      fatal_error("Error in \"delete\" rule");
    else {
      Black_rules = plist_append(Black_rules, ce);
      if (rule_contains_semantics(ce))
	Rule_needs_semantics = TRUE;
    }
  }
}
