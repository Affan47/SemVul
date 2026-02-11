programmable_completions (cmd, word, start, end, foundp)
     const char *cmd;
     const char *word;
     int start, end, *foundp;
{
  COMPSPEC *cs, *lastcs;
  STRINGLIST *ret;
  char **rmatches, *t;
  int found, retry, count;

  lastcs = 0;
  found = count = 0;

  do
    {
      retry = 0;


      ret = gen_progcomp_completions (cmd, cmd, word, start, end, &found, &retry, &lastcs);
      if (found == 0)
	{
	  t = strrchr (cmd, '/');
	  if (t && *(++t))
	    ret = gen_progcomp_completions (t, cmd, word, start, end, &found, &retry, &lastcs);
	}

      if (found == 0)
	ret = gen_progcomp_completions (DEFAULTCMD, cmd, word, start, end, &found, &retry, &lastcs);

      count++;

      if (count > 32)
	{
	  internal_warning ("programmable_completion: %s: possible retry loop", cmd);
	  break;
	}
    }
  while (retry);

  if (ret)
    {
      rmatches = ret->list;
      free (ret);
    }
  else
    rmatches = (char **)NULL;

  if (foundp)
    *foundp = found;

  if (lastcs)
    compspec_dispose (lastcs);

  return (rmatches);
}
