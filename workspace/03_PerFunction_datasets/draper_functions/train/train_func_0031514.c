handle_options (unsigned int argc, const char **argv, unsigned int lang_mask)
{
  unsigned int n, i;

  for (i = 1; i < argc; i += n)
    {
      const char *opt = argv[i];


      if (opt[0] != '-' || opt[1] == '\0')
	{
	  if (main_input_filename == NULL)
	    main_input_filename = opt;
	  add_input_filename (opt);
	  n = 1;
	  continue;
	}

      n = handle_option (argv + i, lang_mask);

      if (!n)
	{
	  n = 1;
	  error ("unrecognized command line option \"%s\"", opt);
	}
    }
}
