hack_braces_completion (names)
     char **names;
{
  register int i;
  char *temp;

  i = strvec_len (names);
  if (MB_CUR_MAX > 1 && i > 2)
    qsort (names+1, i-1, sizeof (char *), (QSFUNC *)_strcompare);

  temp = really_munge_braces (names, 1, i, 0);

  for (i = 0; names[i]; ++i)
    {
      free (names[i]);
      names[i] = NULL;
    }
  names[0] = temp;
  return 0;
}
