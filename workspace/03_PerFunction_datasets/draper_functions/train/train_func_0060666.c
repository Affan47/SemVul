get_use_iv_cost (struct ivopts_data *data, struct iv_use *use,
		 struct iv_cand *cand)
{
  unsigned i, s;
  struct cost_pair *ret;

  if (!cand)
    return NULL;

  if (data->consider_all_candidates)
    {
      ret = use->cost_map + cand->id;
      if (!ret->cand)
	return NULL;

      return ret;
    }


  s = cand->id & (use->n_map_members - 1);
  for (i = s; i < use->n_map_members; i++)
    if (use->cost_map[i].cand == cand)
      return use->cost_map + i;
    else if (use->cost_map[i].cand == NULL)
      return NULL;
  for (i = 0; i < s; i++)
    if (use->cost_map[i].cand == cand)
      return use->cost_map + i;
    else if (use->cost_map[i].cand == NULL)
      return NULL;

  return NULL;
}
