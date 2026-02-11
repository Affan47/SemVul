option_enabled (int opt_idx, void *opts)
{
  const struct cl_option *option = &(cl_options[opt_idx]);
  struct gcc_options *optsg = (struct gcc_options *) opts;
  void *flag_var = option_flag_var (opt_idx, optsg);

  if (flag_var)
    switch (option->var_type)
      {
      case CLVC_BOOLEAN:
	return *(int *) flag_var != 0;

      case CLVC_EQUAL:
	return *(int *) flag_var == option->var_value;

      case CLVC_BIT_CLEAR:
	return (*(int *) flag_var & option->var_value) == 0;

      case CLVC_BIT_SET:
	return (*(int *) flag_var & option->var_value) != 0;

      case CLVC_STRING:
      case CLVC_ENUM:
      case CLVC_DEFER:
	break;
      }
  return -1;
}
