hira2kata(gchar *hirastr) {
  gchar *hiraptr;
  gchar *kata = g_new0(gchar, strlen(hirastr) + 6);
  gchar *kataptr = kata;
  int length;

  hiraptr = hirastr;
  while (*hiraptr != 0) {
    if (isHiraganaChar(g_utf8_get_char(hiraptr)) == TRUE) {
      g_unichar_to_utf8(g_utf8_get_char(hiraptr) + 96, kataptr);
    }
    else {
      length = g_utf8_next_char(hiraptr) - hiraptr;
      strncat(kataptr, hiraptr, length);
      kataptr[length + 1] = 0;
    }
    kataptr = g_utf8_next_char(kataptr);
    hiraptr = g_utf8_next_char(hiraptr);
    if (hiraptr == NULL) break;
  }
  return kata;
}
