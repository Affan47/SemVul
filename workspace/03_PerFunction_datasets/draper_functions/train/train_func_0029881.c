iv_ca_prune (struct ivopts_data *data, struct iv_ca *ivs,
	     struct iv_cand *except_cand, struct iv_ca_delta **delta)
{
  bitmap_iterator bi;
  struct iv_ca_delta *act_delta, *best_delta;
  unsigned i;
  comp_cost best_cost, acost;
  struct iv_cand *cand;

  best_delta = NULL;
  best_cost = iv_ca_cost (ivs);

  EXECUTE_IF_SET_IN_BITMAP (ivs->cands, 0, i, bi)
    {
      cand = iv_cand (data, i);

      if (cand == except_cand)
	continue;

      acost = iv_ca_narrow (data, ivs, cand, &act_delta);

      if (compare_costs (acost, best_cost) < 0)
	{
	  best_cost = acost;
	  iv_ca_delta_free (&best_delta);
	  best_delta = act_delta;
	}
      else
	iv_ca_delta_free (&act_delta);
    }

  if (!best_delta)
    {
      *delta = NULL;
      return best_cost;
    }


  iv_ca_delta_commit (data, ivs, best_delta, true);
  best_cost = iv_ca_prune (data, ivs, except_cand, delta);
  iv_ca_delta_commit (data, ivs, best_delta, false);
  *delta = iv_ca_delta_join (best_delta, *delta);
  return best_cost;
}
