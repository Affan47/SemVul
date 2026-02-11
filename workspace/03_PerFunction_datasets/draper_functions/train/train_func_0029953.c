gm_string_trim(const gchar *str) {
  gchar *newstr = NULL;
  const gchar *r, *l;

  if (str == NULL) {
    return NULL;
  }

  r = str + strlen(str);
  l = str;

  while (*l == ' ' || *r == ' ') {
    if (l == r) {
      break;
    }

    if (*l == ' ') {
      l++;
    }

    if (l == r) {
      break;
    }

    if (*r == ' ') {
      r--;
    }
  }

  if (l == r) {
    return g_strdup("");
  } else {
    newstr = g_strndup(l, r - l);
    return newstr;
  }
}
