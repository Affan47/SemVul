display_signal_list (list, forcecols)
     WORD_LIST *list;
     int forcecols;
{
  register int i, column;
  char *name;
  int result, signum, dflags;
  intmax_t lsignum;

  result = EXECUTION_SUCCESS;
  if (!list)
    {
      for (i = 1, column = 0; i < NSIG; i++)
	{
	  name = signal_name (i);
	  if (STREQN (name, "SIGJUNK", 7) || STREQN (name, "Unknown", 7))
	    continue;

	  if (posixly_correct && !forcecols)
	    {


	      if (STREQN (name, "SIG", 3))
		name += 3;
	      printf ("%s%s", name, (i == NSIG - 1) ? "" : " ");
	    }
	  else
	    {
	      printf ("%2d) %s", i, name);

	      if (++column < 5)
		printf ("\t");
	      else
		{
		  printf ("\n");
		  column = 0;
		}
	    }
	}

      if ((posixly_correct && !forcecols) || column != 0)
	printf ("\n");
      return result;
    }


  while (list)
    {
      if (legal_number (list->word->word, &lsignum))
	{


	  if (lsignum > 128)
	    lsignum -= 128;
	  if (lsignum < 0 || lsignum >= NSIG)
	    {
	      sh_invalidsig (list->word->word);
	      result = EXECUTION_FAILURE;
	      list = list->next;
	      continue;
	    }

	  signum = lsignum;
	  name = signal_name (signum);
	  if (STREQN (name, "SIGJUNK", 7) || STREQN (name, "Unknown", 7))
	    {
	      list = list->next;
	      continue;
	    }
#if defined (JOB_CONTROL)


	  printf ("%s\n", (this_shell_builtin == kill_builtin) ? name + 3 : name);
#else
	  printf ("%s\n", name);
#endif
	}
      else
	{
	  dflags = DSIG_NOCASE;
	  if (posixly_correct == 0 || this_shell_builtin != kill_builtin)
	    dflags |= DSIG_SIGPREFIX;
	  signum = decode_signal (list->word->word, dflags);
	  if (signum == NO_SIG)
	    {
	      sh_invalidsig (list->word->word);
	      result = EXECUTION_FAILURE;
	      list = list->next;
	      continue;
	    }
	  printf ("%d\n", signum);
	}
      list = list->next;
    }
  return (result);
}
