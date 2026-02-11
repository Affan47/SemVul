get_word(char *str, char *source, char t)
{
  int i = 0;
  char current;

  do
  {
    current = *source;

    if((current == '\\') && (source[1] == '"'))
    {
      str[i] = '"';
      source++;
      current = 'x';
    }
    else
    {
      str[i] = current;
    }

    source++;
    i++;

  } while((current != t) && (current != 0) && (i < 256));

  str[i - 1] = 0;
}
