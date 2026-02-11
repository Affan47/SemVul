get_format(char **rtn, char *fmt,
                               const struct strobe_cb_info *info, unsigned int *idx)
{
  char *cp = fmt;
  unsigned int size;

  *rtn = strdup("");
  size = 1;
  while (*cp) {
    size_t cnt = strcspn(cp, "%");

    if (cnt > 0) {
      *rtn = realloc(*rtn, (size+cnt)*sizeof(char));
      memcpy(*rtn+size-1, cp, cnt);
      size += cnt;
      cp += cnt;
    } else {
      int ljust = 0, plus = 0, ld_zero = 0, width = -1, prec = -1;
      char *result;

      cp += 1;
      while ((*cp == '-') || (*cp == '+')) {
        if (*cp == '-') ljust = 1;
        else plus = 1;
        cp += 1;
      }
      if (*cp == '0') {
        ld_zero = 1;
        cp += 1;
      }
      if (isdigit((int)*cp)) width = strtoul(cp, &cp, 10);
      if (*cp == '.') {
        cp += 1;
        prec = strtoul(cp, &cp, 10);
      }
      cnt = get_format_char(&result, ljust, plus, ld_zero, width, prec, *cp,
                            info, idx);
      *rtn = realloc(*rtn, (size+cnt)*sizeof(char));
      memcpy(*rtn+size-1, result, cnt);
      free(result);
      size += cnt;
      if (*cp) cp += 1;
    }
  }
  *(*rtn+size-1) = '\0';
  return size - 1;
}
