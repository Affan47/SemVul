zxid_eval_squash_env(char* vorig, const char* exp, char* env_hdr, char* n, char* lim, int squash_type)
{
  int len;
  char* val = getenv(env_hdr);
  if (!val) {
    if (--zxid_suppress_vpath_warning > 0) ERR("VPATH or VURL(%s) %s expansion specified, but env(%s) not defined?!? Violation of CGI spec? SERVER_SOFTWARE(%s)", vorig, exp, env_hdr, STRNULLCHKQ(getenv("SERVER_SOFTWARE")));
    return 0;
  }
  len = strlen(val);
  if (n + len > lim) {
    ERR("TOO LONG: VPATH or VURL(%s) %s expansion specified env(%s) val(%s) does not fit, missing %ld bytes. SERVER_SOFTWARE(%s)", vorig, exp, env_hdr, val, (long)(lim - (n + len)), STRNULLCHKQ(getenv("SERVER_SOFTWARE")));
    return 0;
  }


  for (; *val; ++val, ++n)
    if (!squash_type && IN_RANGE(*val, 'A', 'Z')) {
      *n = *val - ('A' - 'a');
    } else if (IN_RANGE(*val, 'a', 'z') || IN_RANGE(*val, '0', '9') || ONE_OF_2(*val, '.', '-')) {
      *n = *val;
    } else if (squash_type == 1 && ONE_OF_5(*val, '/', ':', '?', '&', '=')) {
      *n = *val;
    } else {
      *n = '_';
    }
  return len;
}
