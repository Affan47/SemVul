grammar_rules_partial_print (FILE *out, const char *title,
                             rule_filter filter)
{
  rule_number r;
  bool first = true;
  symbol *previous_lhs = NULL;


  for (r = 0; r < nrules + nuseless_productions; r++)
    {
      if (filter && !filter (&rules[r]))
        continue;
      if (first)
        fprintf (out, "%s\n\n", title);
      else if (previous_lhs && previous_lhs != rules[r].lhs)
        fputc ('\n', out);
      first = false;
      rule_lhs_print (&rules[r], previous_lhs, out);
      rule_rhs_print (&rules[r], out);
      fprintf (out, "\n");
      previous_lhs = rules[r].lhs;
    }
  if (!first)
    fputs ("\n\n", out);
}
