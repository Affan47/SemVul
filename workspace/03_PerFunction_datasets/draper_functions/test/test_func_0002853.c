match_pattern_char (pat, string)
     char *pat, *string;
{
  char c;

  if (*string == 0)
    return (0);

  switch (c = *pat++)
    {
    default:
      return (*string == c);
    case '\\':
      return (*string == *pat);
    case '?':
      return (*pat == LPAREN ? 1 : (*string != '\0'));
    case '*':
      return (1);
    case '+':
    case '!':
    case '@':
      return (*pat == LPAREN ? 1 : (*string == c));
    case '[':
      return (*string != '\0');
    }
}
