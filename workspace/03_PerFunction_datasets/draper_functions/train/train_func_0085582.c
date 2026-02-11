decode_stripchart_config(uschar *s)
{
int i;


for (i = 0; i <= 1; i++)

  {
  int first = 1;
  int count = 0;
  uschar *p = s;

  if (*p == '/') p++;


  while (*p)
    {
    uschar *pp;

    if (*p == '\n')
      {
      while (*(++p) == ' ' || *p == '\t');
      if (*p == '/') p++;
      }


    pp = p;
    while (*p && *p != '/') p++;
    if (first) count++;


    if (i != 0)
      {
      uschar buffer[256];
      int indx = count + stripchart_varstart - 1;
      Ustrncpy(buffer, pp, p-pp);
      buffer[p-pp] = 0;
      if (first)
        {
        int offset;
        const uschar *error;
        stripchart_regex[indx] = pcre_compile(CS buffer, PCRE_COPT,
          (const char **)&error, &offset, NULL);
        if (stripchart_regex[indx] == NULL)
          {
          printf("regular expression error: %s at offset %d "
            "while compiling %s\n", error, offset, buffer);
          exit(99);
          }
        }
      else stripchart_title[indx] = string_copy(buffer);
      }


    p++;
    first = !first;
    }


  if (i == 0)
    {
    stripchart_number += count;
    stripchart_regex = (pcre **)store_malloc(stripchart_number * sizeof(pcre *));
    stripchart_title = (uschar **)store_malloc(stripchart_number * sizeof(uschar *));
    }
  }
}
