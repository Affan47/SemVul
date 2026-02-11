fc_strrep(char *str, size_t len, const char *search,
               const char *replace)
{
  size_t len_search, len_replace;
  char *s, *p;

  fc_assert_ret_val(str != NULL, FALSE);
  if (search == NULL || replace == NULL) {
    return TRUE;
  }

  len_search = strlen(search);
  len_replace = strlen(replace);

  s = str;
  while (s != NULL) {
    p = strstr(s, search);
    if (p == NULL) {

      break;
    }

    if (len < (strlen(str) + len_replace - len_search + 1)) {

      return FALSE;
    }

    memmove(p + len_replace, p + len_search, strlen(p + len_search) + 1);
    memcpy(p, replace, len_replace);
    s = p + len_replace;
  }

  return TRUE;
}
