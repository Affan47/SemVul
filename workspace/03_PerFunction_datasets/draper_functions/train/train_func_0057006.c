Bound_Var(WamWord *adr)
{
  long *p;

  for (p = glob_dico_var; p < bound_var_ptr; p++)
    if (*p == (long) adr)
      return;

  if (bound_var_ptr - glob_dico_var >= MAX_VAR_IN_TERM)
    Pl_Err_Representation(representation_too_many_variables);

  *bound_var_ptr++ = (long) adr;
}
