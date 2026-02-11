expand_amble (text, tlen, flags)
     char *text;
     size_t tlen;
     int flags;
{
  char **result, **partial;
  char *tem;
  int start, i, c;

  DECLARE_MBSTATE;

  result = (char **)NULL;

  start = i = 0;
  c = 1;
  while (c)
    {
      c = brace_gobbler (text, tlen, &i, brace_arg_separator);
#if defined (SHELL)
      tem = substring (text, start, i);
#else
      tem = (char *)xmalloc (1 + (i - start));
      strncpy (tem, &text[start], (i - start));
      tem[i- start] = '\0';
#endif

      partial = brace_expand (tem);

      if (!result)
	result = partial;
      else
	{
	  register int lr, lp, j;

	  lr = strvec_len (result);
	  lp = strvec_len (partial);

	  result = strvec_resize (result, lp + lr + 1);

	  for (j = 0; j < lp; j++)
	    result[lr + j] = partial[j];

	  result[lr + j] = (char *)NULL;
	  free (partial);
	}
      free (tem);
      ADVANCE_CHAR (text, tlen, i);
      start = i;
    }
  return (result);
}
