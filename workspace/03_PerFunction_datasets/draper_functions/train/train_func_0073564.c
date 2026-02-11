extract_string (FILE *stream)
{
  int c;
  size_t nread = 0;
  size_t strsize = 100;
  char *str = mpc_alloc_str (strsize);
  size_t lenstr;

  c = getc (stream);
  while (c != EOF && c != '\n'
         && !isspace ((unsigned char) c)
         && c != '(' && c != ')') {
    str [nread] = (char) c;
    nread++;
    if (nread == strsize) {
      str = mpc_realloc_str (str, strsize, 2 * strsize);
      strsize *= 2;
    }
    c = getc (stream);
  }

  str = mpc_realloc_str (str, strsize, nread + 1);
  strsize = nread + 1;
  str [nread] = '\0';

  if (nread == 0)
    return str;

  lenstr = nread;

  if (c == '(') {
    size_t n;
    char *suffix;
    int ret;


    if ((nread != 3
         || tolower ((unsigned char) (str[0])) != 'n'
         || tolower ((unsigned char) (str[1])) != 'a'
         || tolower ((unsigned char) (str[2])) != 'n')
        && (nread != 5
            || str[0] != '@'
            || tolower ((unsigned char) (str[1])) != 'n'
            || tolower ((unsigned char) (str[2])) != 'a'
            || tolower ((unsigned char) (str[3])) != 'n'
            || str[4] != '@')) {
      ungetc (c, stream);
      return str;
    }

    suffix = extract_suffix (stream);
    nread += strlen (suffix) + 1;
    if (nread >= strsize) {
      str = mpc_realloc_str (str, strsize, nread + 1);
      strsize = nread + 1;
    }


    ret = sprintf (str + lenstr, "(%s", suffix);
    MPC_ASSERT (ret >= 0);
    n = lenstr + (size_t) ret;
    MPC_ASSERT (n == nread);

    c = getc (stream);
    if (c == ')') {
      str = mpc_realloc_str (str, strsize, nread + 2);
      strsize = nread + 2;
      str [nread] = (char) c;
      str [nread+1] = '\0';
      nread++;
    }
    else if (c != EOF)
      ungetc (c, stream);

    mpc_free_str (suffix);
  }
  else if (c != EOF)
    ungetc (c, stream);

  return str;
}
