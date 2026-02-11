get_common_prefix(const char *const *prefixes,
                                size_t num_prefixes,
                                char *buf, size_t buf_len)
{
  const char *p;
  char *q;
  size_t i;

  fc_strlcpy(buf, prefixes[0], buf_len);
  for (i = 1; i < num_prefixes; i++) {
    for (p = prefixes[i], q = buf; *p != '\0' && *q != '\0';
         p = g_utf8_next_char(p), q = g_utf8_next_char(q)) {
      if (g_unichar_toupper(g_utf8_get_char(p))
          != g_unichar_toupper(g_utf8_get_char(q))) {
        *q = '\0';
        break;
      }
    }
  }

 return g_utf8_strlen(buf, -1);
}
