is_or_set_subset_of (norm_cond_t norm_cond1,
                     norm_cond_t norm_cond2)
{
  size_t i;
  size_t len = VEC_length (gimple, norm_cond1->conds);

  for (i = 0; i < len; i++)
    {
      if (!is_subset_of_any (VEC_index (gimple, norm_cond1->conds, i),
                             false, norm_cond2, false))
        return false;
    }
  return true;
}
