__opt_process_options(struct opt_odb_t *odb,
		      int argc,
		      char **argv,
		      int depth)
{
  int index, do_dumpconfig;
  char *dumpconfig_name;

  index = 0;
  do_dumpconfig = FALSE;
  dumpconfig_name = NULL;

  while (index < argc)
    {

      while (index < argc && argv[index][0] != '-')
	{
	  if (depth > 0)
	    {

	      fatal("orphan `%s' encountered during config file processing",
		    argv[index]);
	    }

	  if (odb->orphan_fn)
	    {
	      if (!odb->orphan_fn(index+1, argc, argv))
		{

		  goto done_processing;
		}
	    }
	  else
	    {

	      fatal("orphan argument `%s' was unclaimed", argv[index]);
	    }

	}


      if (index == argc)
	{

	  goto done_processing;
	}


      if (!strcmp(argv[index], "-config"))
	{

	  index++;
	  if (index >= argc || argv[index][0] == '-')
	    {

	      fatal("option `-config' requires an argument");
	    }
	  process_file(odb, argv[index], depth);
	  index++;
	}
      else if (!strcmp(argv[index], "-dumpconfig"))
	{

	  do_dumpconfig = TRUE;

	  index++;
	  if (index >= argc
	      || (argv[index][0] == '-' && argv[index][1] != '\0'))
	    {

	      fatal("option `-dumpconfig' requires an argument");
	    }
	  dumpconfig_name = argv[index];
	  index++;
	}
      else
	{

	  index = process_option(odb, index, argc, argv);
	}
    }
 done_processing:

  if (do_dumpconfig)
    dump_config(odb, dumpconfig_name);
}
