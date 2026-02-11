main (int argc ATTRIBUTE_UNUSED, char **argv)
{
  int opt;


  unlock_std_streams ();

  while ((opt = getopt_long (argc, argv, "hlpv", options, NULL)) != -1)
    {
      switch (opt)
	{
	case 'h':
	  print_usage ();
	  break;
	case 'v':
	  print_version ();
	  break;
	case 'l':
	  flag_dump_contents = 1;
	  break;
	case 'p':
	  flag_dump_positions = 1;
	  break;
	default:
	  fprintf (stderr, "unknown flag `%c'\n", opt);
	}
    }

  while (argv[optind])
    dump_file (argv[optind++]);
  return 0;
}
