add_string(char **bufpos, const char *string, size_t stringlen, char **bufstart, size_t *buflen)
{

  if ((*bufpos - *bufstart) + stringlen > *buflen)
    {
      char *new = realloc(*bufstart, *buflen * 2);
      if (!new)
        {
          printf("[%s]\n", _("Error allocating memory"));
          exit(1);
        }
      *buflen *= 2;
      *bufpos = new + (*bufpos - *bufstart);
      *bufstart = new;
    }


  strncpy(*bufpos, string, stringlen);
  *bufpos += stringlen;
}
