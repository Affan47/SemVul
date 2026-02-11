opal_argv_join(char **argv, int delimiter)
{
  char **p;
  char *pp;
  char *str;
  size_t str_len = 0;
  size_t i;


  if (NULL == argv || NULL == argv[0]) {
      return strdup("");
  }


  for (p = argv; *p; ++p) {
    str_len += strlen(*p) + 1;
  }


  if (NULL == (str = (char*) malloc(str_len)))
    return NULL;


  str[--str_len] = '\0';
  p = argv;
  pp = *p;

  for (i = 0; i < str_len; ++i) {
    if ('\0' == *pp) {


      str[i] = (char) delimiter;
      ++p;
      pp = *p;
    } else {
      str[i] = *pp++;
    }
  }


  return str;
}
