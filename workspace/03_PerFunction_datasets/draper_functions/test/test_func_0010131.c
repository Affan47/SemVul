_cmdline_parse (int argc, char **argv)
{
  char options[100];
  int c;

#if HAVE_GETOPT_LONG
  struct option long_options[] =
    {
      { "help",                0, NULL, 'h'},
      { "version",             0, NULL, 'v'},
#ifndef NDEBUG
      { "config-file",         1, NULL, 'c'},
      { "debug",               0, NULL, 'd'},
#endif
      { NULL,                  0, NULL, 0},
    };
#endif

  assert (argv);

  memset (options, '\0', sizeof (options));
  strcat (options, "hv");
#ifndef NDEBUG
  strcat (options, "c:d");
#endif


  opterr = 0;

#if HAVE_GETOPT_LONG
  while ((c = getopt_long (argc, argv, options, long_options, NULL)) != -1)
#else
    while ((c = getopt (argc, argv, options)) != -1)
#endif
      {
    switch (c)
      {
      case 'h':
        _usage ();
        break;
      case 'v':
        _version ();
        break;
#ifndef NDEBUG
      case 'c':
        if (!(conf.config_file = strdup (optarg)))
          IPMIDETECTD_EXIT (("strdup: %s", strerror (errno)));
        break;
      case 'd':
        conf.debug++;
        break;
#endif
      case '?':
      default:
        IPMIDETECTD_EXIT (("unknown command line option '%c'", c));
      }
      }
}
