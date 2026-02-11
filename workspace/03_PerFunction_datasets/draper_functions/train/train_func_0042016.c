main (int argc, char **argv)
{

  int can_mode = -1;
  int status = EXIT_SUCCESS;
  int optc;
  bool use_nuls = false;

  initialize_main (&argc, &argv);
  set_program_name (argv[0]);
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  atexit (close_stdout);

  while ((optc = getopt_long (argc, argv, "efmnqsvz", longopts, NULL)) != -1)
    {
      switch (optc)
        {
        case 'e':
          can_mode = CAN_EXISTING;
          break;
        case 'f':
          can_mode = CAN_ALL_BUT_LAST;
          break;
        case 'm':
          can_mode = CAN_MISSING;
          break;
        case 'n':
          no_newline = true;
          break;
        case 'q':
        case 's':
          verbose = false;
          break;
        case 'v':
          verbose = true;
          break;
        case 'z':
          use_nuls = true;
          break;
        case_GETOPT_HELP_CHAR;
        case_GETOPT_VERSION_CHAR (PROGRAM_NAME, AUTHORS);
        default:
          usage (EXIT_FAILURE);
        }
    }

  if (optind >= argc)
    {
      error (0, 0, _("missing operand"));
      usage (EXIT_FAILURE);
    }

  if (argc - optind > 1)
    {
      if (no_newline)
        error (0, 0, _("ignoring --no-newline with multiple arguments"));
      no_newline = false;
    }

  for (; optind < argc; ++optind)
    {
      const char *fname = argv[optind];
      char *value = (can_mode != -1
                     ? canonicalize_filename_mode (fname, can_mode)
                     : areadlink_with_size (fname, 63));
      if (value)
        {
          fputs (value, stdout);
          if (! no_newline)
            putchar (use_nuls ? '\0' : '\n');
          free (value);
        }
      else
        {
          status = EXIT_FAILURE;
          if (verbose)
            error (0, errno, "%s", fname);
        }
    }

  return status;
}
