bash_tilde_expand (s, assign_p)
     const char *s;
     int assign_p;
{
  int old_immed, old_term, r;
  char *ret;

  old_immed = interrupt_immediately;
  old_term = terminate_immediately;
  interrupt_immediately = terminate_immediately = 1;

  tilde_additional_prefixes = assign_p == 0 ? (char **)0
  					    : (assign_p == 2 ? bash_tilde_prefixes2 : bash_tilde_prefixes);
  if (assign_p == 2)
    tilde_additional_suffixes = bash_tilde_suffixes2;

  r = (*s == '~') ? unquoted_tilde_word (s) : 1;
  ret = r ? tilde_expand (s) : savestring (s);
  interrupt_immediately = old_immed;
  terminate_immediately = old_term;
  return (ret);
}
