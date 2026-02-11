get_init_value (dataflow_set *set, rtx loc, decl_or_value dv)
{
  variable var;
  int i;
  enum var_init_status ret_val = VAR_INIT_STATUS_UNKNOWN;

  if (! flag_var_tracking_uninit)
    return VAR_INIT_STATUS_INITIALIZED;

  var = shared_hash_find (set->vars, dv);
  if (var)
    {
      for (i = 0; i < var->n_var_parts && ret_val == VAR_INIT_STATUS_UNKNOWN; i++)
	{
	  location_chain nextp;
	  for (nextp = var->var_part[i].loc_chain; nextp; nextp = nextp->next)
	    if (rtx_equal_p (nextp->loc, loc))
	      {
		ret_val = nextp->init;
		break;
	      }
	}
    }

  return ret_val;
}
