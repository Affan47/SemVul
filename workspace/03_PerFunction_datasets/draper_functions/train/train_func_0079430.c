main (int argc, char **argv)
{
  int argno;


  unlock_std_streams ();

  gcc_init_libintl ();


  expandargv (&argc, &argv);

  argno = process_args (argc, argv);
  if (optind == argc)
    print_usage (true);

  if (argc - argno > 1)
    multiple_files = 1;

  for (; argno != argc; argno++)
    process_file (argv[argno]);

  generate_results (multiple_files ? NULL : argv[argc - 1]);

  release_structures ();

  return 0;
}
