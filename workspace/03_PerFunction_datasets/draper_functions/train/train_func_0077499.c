is_or_set_subset_of (norm_cond_t norm_cond1,
                     norm_cond_t norm_cond2)
{
  size_t i;
  size_t len = norm_cond1->conds.length ();

  for (i = 0; i < len; i++)
    {
      if (!is_subset_of_any (norm_cond1->conds[i],
                             false, norm_cond2, false))
        return false;
    }
  return true;
}
