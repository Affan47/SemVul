remove_duplicate_matches (matches)
     char **matches;
{
  char *lowest_common;
  int i, j, newlen;
  char dead_slot;
  char **temp_array;


  for (i = 0; matches[i]; i++)
    ;


  if (i && rl_sort_completion_matches)
    qsort (matches+1, i-1, sizeof (char *), (QSFUNC *)_rl_qsort_string_compare);


  lowest_common = savestring (matches[0]);

  for (i = newlen = 0; matches[i + 1]; i++)
    {
      if (strcmp (matches[i], matches[i + 1]) == 0)
	{
	  free (matches[i]);
	  matches[i] = (char *)&dead_slot;
	}
      else
	newlen++;
    }


  temp_array = (char **)xmalloc ((3 + newlen) * sizeof (char *));
  for (i = j = 1; matches[i]; i++)
    {
      if (matches[i] != (char *)&dead_slot)
	temp_array[j++] = matches[i];
    }
  temp_array[j] = (char *)NULL;

  if (matches[0] != (char *)&dead_slot)
    free (matches[0]);


  temp_array[0] = lowest_common;


  if (j == 2 && strcmp (temp_array[0], temp_array[1]) == 0)
    {
      free (temp_array[1]);
      temp_array[1] = (char *)NULL;
    }
  return (temp_array);
}
