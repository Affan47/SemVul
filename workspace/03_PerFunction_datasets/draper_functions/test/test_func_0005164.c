umask_builtin (list)
     WORD_LIST *list;
{
  int print_symbolically, opt, umask_value, pflag;
  mode_t umask_arg;

  print_symbolically = pflag = 0;
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "Sp")) != -1)
    {
      switch (opt)
	{
	case 'S':
	  print_symbolically++;
	  break;
	case 'p':
	  pflag++;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }

  list = loptend;

  if (list)
    {
      if (DIGIT (*list->word->word))
	{
	  umask_value = read_octal (list->word->word);


	  if (umask_value == -1)
	    {
	      sh_erange (list->word->word, _("octal number"));
	      return (EXECUTION_FAILURE);
	    }
	}
      else
	{
	  umask_value = symbolic_umask (list);
	  if (umask_value == -1)
	    return (EXECUTION_FAILURE);
	}
      umask_arg = (mode_t)umask_value;
      umask (umask_arg);
      if (print_symbolically)
	print_symbolic_umask (umask_arg);
    }
  else
    {
      umask_arg = umask (022);
      umask (umask_arg);

      if (pflag)
	printf ("umask%s ", (print_symbolically ? " -S" : ""));
      if (print_symbolically)
	print_symbolic_umask (umask_arg);
      else
	printf ("%04lo\n", (unsigned long)umask_arg);
    }

  return (sh_chkwrite (EXECUTION_SUCCESS));
}
