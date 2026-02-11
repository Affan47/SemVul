add_derived_ivs_candidates (struct ivopts_data *data)
{
  unsigned i;

  for (i = 0; i < n_iv_uses (data); i++)
    {
      struct iv_use *use = iv_use (data, i);

      if (!use)
	continue;

      switch (use->type)
	{
	case USE_NONLINEAR_EXPR:
	case USE_COMPARE:
	case USE_ADDRESS:

	  add_iv_value_candidates (data, use->iv, use);
	  break;

	default:
	  gcc_unreachable ();
	}
    }
}
