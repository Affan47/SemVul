end_alias_analysis ()
{
  reg_known_value = 0;
  reg_known_value_size = 0;
  free (reg_known_equiv_p);
  reg_known_equiv_p = 0;
  reg_base_value = 0;
  reg_base_value_size = 0;
  if (alias_invariant)
    {
      alias_invariant = 0;
      alias_invariant_size = 0;
    }
}
