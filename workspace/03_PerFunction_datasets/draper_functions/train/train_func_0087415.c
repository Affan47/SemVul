starts_with_word(const char *line, const char *word)
{
  int i = 0;
  for (i=0; word[i]; i++)
  {
    if (!line[i])
    {

      return 0;
    }
    if (line[i] != word[i])
    {

      return 0;
    }
  }
  if (!line[i])
  {

    return 1;
  }
  if (isspace(line[i]))
  {

    return 1;
  }

  return 0;
}
