hash_builtin (list)
     WORD_LIST *list;
{
  int expunge_hash_table, list_targets, list_portably, delete, opt;
  char *w, *pathname;

  if (hashing_enabled == 0)
    {
      builtin_error (_("hashing disabled"));
      return (EXECUTION_FAILURE);
    }

  expunge_hash_table = list_targets = list_portably = delete = 0;
  pathname = (char *)NULL;
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "dlp:rt")) != -1)
    {
      switch (opt)
	{
	case 'd':
	  delete = 1;
	  break;
	case 'l':
	  list_portably = 1;
	  break;
	case 'p':
	  pathname = list_optarg;
	  break;
	case 'r':
	  expunge_hash_table = 1;
	  break;
	case 't':
	  list_targets = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }
  list = loptend;


  if (list == 0 && list_targets)
    {
      sh_needarg ("-t");
      return (EXECUTION_FAILURE);
    }


  if (list == 0 && expunge_hash_table == 0)
    {
      opt = print_hashed_commands (list_portably);
      if (opt == 0 && posixly_correct == 0)
	printf (_("%s: hash table empty\n"), this_command_name);

      return (EXECUTION_SUCCESS);
    }

  if (expunge_hash_table)
    phash_flush ();


  if (list_targets)
    return (list_hashed_filename_targets (list, list_portably));

#if defined (RESTRICTED_SHELL)
  if (restricted && pathname && strchr (pathname, '/'))
    {
      sh_restricted (pathname);
      return (EXECUTION_FAILURE);
    }
#endif

  for (opt = EXECUTION_SUCCESS; list; list = list->next)
    {

      w = list->word->word;
      if (pathname)
	{
	  if (is_directory (pathname))
	    {
#ifdef EISDIR
	      builtin_error ("%s: %s", pathname, strerror (EISDIR));
#else
	      builtin_error (_("%s: is a directory"), pathname);
#endif
	      opt = EXECUTION_FAILURE;
	    }
	  else
	    phash_insert (w, pathname, 0, 0);
	}
      else if (absolute_program (w))
	continue;
      else if (delete)
	{
	  if (phash_remove (w))
	    {
	      sh_notfound (w);
	      opt = EXECUTION_FAILURE;
	    }
	}
      else if (add_hashed_command (w, 0))
	opt = EXECUTION_FAILURE;
    }

  fflush (stdout);
  return (opt);
}
