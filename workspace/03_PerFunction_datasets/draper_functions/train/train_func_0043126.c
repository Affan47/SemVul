omega_substitute_red_1 (eqn eq, eqn sub, int var, int c, bool *found_black,
			int top_var)
{
  if (eq->coef[var] != 0)
    {
      if (eq->color == omega_black)
	*found_black = true;
      else
	{
	  int j, k = eq->coef[var];

	  eq->coef[var] = 0;

	  for (j = top_var; j >= 0; j--)
	    eq->coef[packing[j]] -= sub->coef[packing[j]] * k * c;
	}
    }
}
