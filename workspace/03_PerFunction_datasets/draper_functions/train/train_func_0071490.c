driver_unknown_option_callback (const struct cl_decoded_option *decoded)
{
  const char *opt = decoded->arg;
  if (opt[1] == 'W' && opt[2] == 'n' && opt[3] == 'o' && opt[4] == '-'
      && !(decoded->errors & CL_ERR_NEGATIVE))
    {


      save_switch (decoded->canonical_option[0],
		   decoded->canonical_option_num_elements - 1,
		   &decoded->canonical_option[1], false);
      return false;
    }
  else
    return true;
}
