shellpattern_match_grab(const char *string,
                                  const char *pattern,
                                  short int casess,
                                  char **match)
{
  regex_t     preg;
  int         numoffsets    = 50;
  regmatch_t  pmatch[numoffsets];
  char        regexp[1024];
  char        *result       = NULL;
  int         flags         = 0;


  strncpy(regexp, pattern, 1023);
  str_replace(regexp, ".", "\\.", 1023);
  str_replace(regexp, "*", ".*", 1023);
  str_replace(regexp, "(", "\\(", 1023);
  str_replace(regexp, ")", "\\)", 1023);
  str_replace(regexp, "?", ".", 1023);
  str_replace(regexp, "[!", "[^", 1023);


  flags = REG_NEWLINE;
  if (!casess)
    flags |= REG_ICASE;
  if (regcomp(&preg, regexp, flags) != 0) {
    fprintf(stderr, "Error: RegExp compilation failed: \"%s\"\n", regexp);
    return(-1);
  }


  if (regexec(&preg, string, numoffsets, pmatch, REG_NOTBOL | REG_NOTEOL) != 0)
    return(1);

  result = (char*)calloc(sizeof(char), (pmatch[1].rm_eo - pmatch[1].rm_so) + 2);
  memcpy(result, string + pmatch[1].rm_so, (pmatch[1].rm_eo - pmatch[1].rm_so));
  *match = result;

  return(0);
}
