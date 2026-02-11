init_action(Term t)
{
  Term rule = copy_term(t);
  Term trigger, stat;

  if (!is_term(rule, "->", 2))
    fatal_error("init_actions, bad rule");
  trigger = ARG(rule,0);
  if (!is_term(trigger, eq_sym(), 2))
    fatal_error("init_actions, bad trigger");
  stat = ARG(trigger,0);

  if (is_constant(stat, "given"))
    Given_rules = plist_append(Given_rules, rule);
  else if (is_constant(stat, "generated"))
    Generated_rules = plist_append(Generated_rules, rule);
  else if (is_constant(stat, "kept"))
    Kept_rules = plist_append(Kept_rules, rule);
  else if (is_constant(stat, "level"))
    Level_rules = plist_append(Level_rules, rule);
  else
    fatal_error("init_action, bad statistic");
}
