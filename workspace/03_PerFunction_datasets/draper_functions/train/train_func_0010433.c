cmdline_parse (int key, char *arg, struct argp_state *state)
{
  struct ipmi_fru_arguments *cmd_args = state->input;
  error_t ret;
  char *endptr;
  int tmp;

  switch (key)
    {
    case DEVICE_ID_KEY:
      errno = 0;
      tmp = strtol (arg, &endptr, 0);
      if (errno
	  || endptr[0] != '\0')
        {
          fprintf (stderr, "invalid device id\n");
          exit (1);
        }

      if (tmp == IPMI_FRU_DEVICE_ID_RESERVED
          || tmp < IPMI_FRU_DEVICE_ID_MIN
          || tmp > IPMI_FRU_DEVICE_ID_MAX)
        {
          fprintf (stderr, "invalid device id\n");
          exit(1);
        }
      cmd_args->device_id = tmp;
      cmd_args->device_id_set++;
      break;
    case VERBOSE_KEY:
      cmd_args->verbose_count++;
      break;
    case SKIP_CHECKS_KEY:
      cmd_args->skip_checks = 1;
      break;
    case INTERPRET_OEM_DATA:
      cmd_args->interpret_oem_data = 1;
      break;
    case ARGP_KEY_ARG:

      argp_usage (state);
      break;
    case ARGP_KEY_END:
      break;
    default:
      ret = common_parse_opt (key, arg, &(cmd_args->common));
      if (ret == ARGP_ERR_UNKNOWN)
        ret = sdr_parse_opt (key, arg, &(cmd_args->sdr));
      if (ret == ARGP_ERR_UNKNOWN)
        ret = hostrange_parse_opt (key, arg, &(cmd_args->hostrange));
      return (ret);
    }

  return (0);
}
