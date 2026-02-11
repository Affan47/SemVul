strncaseprefix(char *prefix, char *word, size_t match_len)
{
  size_t prefix_len, word_len;

  prefix_len = strlen(prefix);
  word_len = strlen(word);
  if (prefix_len > word_len || prefix_len < match_len)
	return(0);

  if (strncaseeq(prefix, word, prefix_len))
	return(1);

  return(0);
}
