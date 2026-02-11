extract_string(char* str)
{
  char *t = str;
  for (char * i = str + 1; *i != '\''; ++i, ++t)
    {
      if (*i == '\\')
        {
          ++i;
          if (*i == 0)
            return 0;
          else if (*i == 't')
            *t = '\t';
          else if (*i == 'n')
            *t = '\n';
          else if (*i == '\\')
            *t = '\\';
          else
            *t = *i;
          continue;
        }

      *t = *i;
    }

  *t = '\0';
  return str;
}
