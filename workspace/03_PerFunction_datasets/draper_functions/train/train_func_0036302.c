history_tokenize_internal (string, wind, indp)
     const char *string;
     int wind, *indp;
{
  char **result;
  register int i, start, result_index, size;


  if (indp && wind != -1)
    *indp = -1;


  for (i = result_index = size = 0, result = (char **)NULL; string[i]; )
    {

      for (; string[i] && whitespace (string[i]); i++)
	;
      if (string[i] == 0 || string[i] == history_comment_char)
	return (result);

      start = i;

      i = history_tokenize_word (string, start);


      if (i == start && history_word_delimiters)
	{
	  i++;
	  while (string[i] && member (string[i], history_word_delimiters))
	    i++;
	}


      if (indp && wind != -1 && wind >= start && wind < i)
        *indp = result_index;

      if (result_index + 2 >= size)
	result = (char **)xrealloc (result, ((size += 10) * sizeof (char *)));

      result[result_index++] = history_substring (string, start, i);
      result[result_index] = (char *)NULL;
    }

  return (result);
}
