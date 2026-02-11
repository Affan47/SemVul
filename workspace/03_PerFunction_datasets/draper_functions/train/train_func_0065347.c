get_option(const char *iarglist, const char *argname)
#endif
{
  size_t arglen = strlen(argname);
  char *arglist;
  char *rval = NULL;
  char *arg;
  char *argp;

  if (!iarglist) {
    return NULL;
  }

  arglen = strlen(argname);
  arglist = xstrdup(iarglist);

  for (arg = arglist; argp = strtok(arg, ","), NULL != argp; arg = NULL) {
    if (0 == case_ignore_strncmp(argp, argname, arglen)) {


      if (argp[arglen] == '=') {
        rval = argp + arglen + 1;
        break;
      } else if (argp[arglen] == '\0') {
        rval = argp;
        break;
      }
    }
  }


  if (rval) {
    rval = xxstrdup(rval,file, line);
  }
  xfree(arglist);
  return rval;
}
