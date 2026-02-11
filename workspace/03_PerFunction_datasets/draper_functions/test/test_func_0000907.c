cmdline_parse (int key, char *arg, struct argp_state *state)
{
  struct ipmi_chassis_config_arguments *cmd_args = state->input;
  error_t ret;

  switch (key)
    {
    case ARGP_KEY_ARG:

      argp_usage (state);
      break;
    case ARGP_KEY_END:
      break;
    default:
      ret = config_parse_opt (key, arg, &cmd_args->config_args);
      if (ret == ARGP_ERR_UNKNOWN)
        ret = common_parse_opt (key, arg, &(cmd_args->config_args.common));
      if (ret == ARGP_ERR_UNKNOWN)
        ret = hostrange_parse_opt (key, arg, &(cmd_args->config_args.hostrange));
      return (ret);
    }

  return (0);
}
