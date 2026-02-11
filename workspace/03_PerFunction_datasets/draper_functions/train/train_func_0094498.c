parse_command_line (int argc, const char *argv[])
{
  int opt = FALSE;


  while ((opt = get_option (argc, argv, s_opts, l_opts)) != EOF)
    {
      switch ((char) opt)
  {
  case 'c':
    nbytes = HDstrdup (opt_arg);
    break;
  case '?':
  default:
    usage (h5tools_getprogname());
    exit (EXIT_FAILURE);
  }
    }

  if (argc <= opt_ind)
    {
      error_msg("missing file name\n");
      usage (h5tools_getprogname());
      exit (EXIT_FAILURE);
    }
}
