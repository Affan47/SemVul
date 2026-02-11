options_parse(int argc, char *argv[])
{
  static struct option long_options[]=
  {
    { "version", no_argument, NULL, OPT_VERSION},
    { "help", no_argument, NULL, OPT_HELP},
    {0, 0, 0, 0},
  };

  bool opt_version= false;
  bool opt_help= false;
  int option_index= 0;

  while (1)
  {
    int option_rv= getopt_long(argc, argv, "", long_options, &option_index);
    if (option_rv == -1)
    {
      break;
    }

    switch (option_rv)
    {
    case OPT_HELP:
      opt_help= true;
      break;

    case OPT_VERSION:
      opt_version= true;
      break;

    case '?':

      exit(EXIT_FAILURE);

    default:
      help_command(argv[0], 1, 0, long_options);
      exit(EXIT_FAILURE);
    }
  }

  if (opt_version)
  {
    version_command(argv[0], 1, 0);
    exit(EXIT_SUCCESS);
  }

  if (opt_help)
  {
    help_command(argv[0], 1, 0, long_options);
    exit(EXIT_SUCCESS);
  }
}
