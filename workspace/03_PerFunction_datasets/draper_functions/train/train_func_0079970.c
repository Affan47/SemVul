parse_opt (int key, char *arg, struct argp_state *state)
{
  char *endptr;
  int v;

  switch (key)
    {
    case 'a':
      add_funix (arg);
      break;

    case 'l':
      LocalHosts = crunch_list (LocalHosts, arg);
      break;

    case 's':
      StripDomains = crunch_list (StripDomains, arg);
      break;

    case 'd':
      Debug = 1;
      NoDetach = 1;
      break;

    case 'h':
      NoHops = 0;
      break;

    case 'r':
      AcceptRemote = 1;
      break;

    case '4':
      usefamily = AF_INET;
      break;

    case '6':
      usefamily = AF_INET6;
      break;

    case OPT_IPANY:
      usefamily = AF_UNSPEC;
      break;

    case 'b':
      BindAddress = arg;
      break;

    case 'B':
      BindPort = arg;
      break;

    case 'm':
      v = strtol (arg, &endptr, 10);
      if (*endptr)
        argp_error (state, "invalid value (`%s' near `%s')", arg, endptr);
      MarkInterval = v * 60;
      break;

    case 'n':
      NoDetach = 1;
      break;

    case OPT_NO_FORWARD:
      NoForward = 1;
      break;

    case OPT_NO_KLOG:
      NoKLog = 1;
      break;

    case OPT_NO_UNIXAF:
      NoUnixAF = 1;
      break;

    case OPT_PIDFILE:
      PidFile = arg;
      break;

    case 'f':
      ConfFile = arg;
      break;

    case 'D':
      ConfDir = arg;
      break;

    case 'p':
      funix[0].name = arg;
      funix[0].fd = -1;
      break;

    case 'S':
      force_sync = 1;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}
