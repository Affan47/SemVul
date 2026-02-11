grammar_current_rule_dprec_set (int dprec, location loc)
{
  if (! glr_parser)
    complain (&loc, Wother, _("%s affects only GLR parsers"),
              "%dprec");
  if (dprec <= 0)
    complain (&loc, complaint, _("%s must be followed by positive number"),
              "%dprec");
  else if (current_rule->dprec != 0)
    duplicate_directive ("%dprec",
                         current_rule->dprec_location, loc);
  else
    {
      current_rule->dprec = dprec;
      current_rule->dprec_location = loc;
    }
}
