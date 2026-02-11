setup_split_channels(stp_vars_t *v)
{
  escp2_privdata_t *pd = get_privdata(v);


  pd->split_channel_count = supports_split_channels(v);
  if (pd->split_channel_count)
    {
      if (pd->res->vres <
	  (escp2_base_separation(v) / escp2_black_nozzle_separation(v)))
	{
	  int incr =
	    (escp2_base_separation(v) / escp2_black_nozzle_separation(v)) /
	    pd->res->vres;
	  pd->split_channel_count /= incr;
	  pd->nozzle_separation *= incr;
	  pd->nozzles /= incr;
	  pd->min_nozzles /= incr;
	}
    }
}
