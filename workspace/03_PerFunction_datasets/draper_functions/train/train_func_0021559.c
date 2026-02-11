parse_options(const int argc, const char** argv)
{
  unsigned int tmp;
  for(int i = 1; i < argc; i++)
    {
      if(strcmp(argv[i], "-can") == 0)
	opt_canonize = true;
      else if((strncmp(argv[i], "-ocan=", 6) == 0) and (strlen(argv[i]) > 6))
	{
	  opt_canonize = true;
	  opt_output_can_file = argv[i]+6;
	}
      else if(sscanf(argv[i], "-v=%u", &tmp) == 1)
	verbose_level = tmp;
      else if(strcmp(argv[i], "-directed") == 0)
	opt_directed = true;
      else if(strcmp(argv[i], "-fr=n") == 0)
	opt_use_failure_recording = false;
      else if(strcmp(argv[i], "-fr=y") == 0)
	opt_use_failure_recording = true;
      else if(strcmp(argv[i], "-cr=n") == 0)
	opt_use_component_recursion = false;
      else if(strcmp(argv[i], "-cr=y") == 0)
	opt_use_component_recursion = true;
      else if((strncmp(argv[i], "-sh=", 4) == 0) and (strlen(argv[i]) > 4))
	{
	  opt_splitting_heuristics = argv[i]+4;
	}
      else if(strcmp(argv[i], "-version") == 0)
	{
	  fprintf(stdout, "bliss version %s\n", bliss::version);
	  exit(0);
	}
      else if(strcmp(argv[i], "-help") == 0)
	{
	  usage(stdout, argv[0]);
	  exit(0);
	}
      else if(argv[i][0] == '-')
	{
	  fprintf(stderr, "Unknown command line argument `%s'\n", argv[i]);
	  usage(stderr, argv[0]);
	  exit(1);
	}
      else
	{
	  if(infilename)
	    {
	      fprintf(stderr, "Too many file arguments\n");
	      usage(stderr, argv[0]);
	      exit(1);
	    }
	  else
	    {
	      infilename = argv[i];
	    }
	}
    }
}
