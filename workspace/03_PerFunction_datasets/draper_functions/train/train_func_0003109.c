cmdline_parse (int key, char *arg, struct argp_state *state)
{
  struct ipmi_raw_arguments *cmd_args = state->input;
  char *endptr;
  int value;
  error_t ret;

  switch (key)
    {
    case CHANNEL_NUMBER_KEY:
      errno = 0;
      value = strtol (arg, &endptr, 0);
      if (errno
          || endptr[0] != '\0'
          || !IPMI_CHANNEL_NUMBER_VALID (value))
        {
          fprintf (stderr, "invalid channel number\n");
          exit (1);
        }
      cmd_args->channel_number_arg = (uint8_t) value;
      cmd_args->channel_number = 1;
      break;
    case SLAVE_ADDRESS_KEY:
      errno = 0;
      value = strtol (arg, &endptr, 0);
      if (errno
          || endptr[0] != '\0')
        {
          fprintf (stderr, "invalid slave address\n");
          exit (1);
        }
      cmd_args->slave_address_arg = (uint8_t) value;
      cmd_args->slave_address = 1;
      break;
    case CMD_FILE_KEY:
      if (!(cmd_args->cmd_file = strdup (arg)))
        {
          perror ("strdup");
          exit (1);
        }
      break;
    case ARGP_KEY_ARG:
      {
        unsigned int i;
        long value;

        if (strlen (arg) >= 2)
          {
            if (!strncmp (arg, "0x", 2))
              arg+=2;
          }

        if (*arg == '\0')
          {
            fprintf (stderr, "invalid hex byte argument\n");
            exit (1);
          }

        for (i = 0; arg[i] != '\0'; i++)
          {
            if (i >= 2)
              {
                fprintf (stderr, "invalid hex byte argument\n");
                exit (1);
              }

            if (!isxdigit (arg[i]))
              {
                fprintf (stderr, "invalid hex byte argument\n");
                exit (1);
              }
          }

	if (cmd_args->cmd_length < IPMI_RAW_MAX_ARGS)
	  {
	    errno = 0;
	    value = strtol (arg, &endptr, 16);
	    if (errno
		|| endptr[0] != '\0')
	      {
		fprintf (stderr, "invalid hex byte argument\n");
		exit (1);
	      }
	    cmd_args->cmd[cmd_args->cmd_length++] = (uint8_t) value;
	  }
	else
	  {
	    fprintf (stderr, "Too many arguments specified\n");
	    exit (1);
	  }

        break;
      }
    case ARGP_KEY_END:
      break;
    default:
      ret = common_parse_opt (key, arg, &(cmd_args->common));
      if (ret == ARGP_ERR_UNKNOWN)
        ret = hostrange_parse_opt (key, arg, &(cmd_args->hostrange));
      return (ret);
    }

  return (0);
}
