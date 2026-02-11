ansitextview_verify_urls_and_add(WorldGUI     *gui,
                                 GtkTextIter  *pos,
                                 const guchar *text,
                                 gsize         len)
{
  static regex_t    regex;
  static gboolean   re_compiled = FALSE;
  static guchar     ctext[MAX_BUFFER + 1];
  static regmatch_t match;
  guint             search_start;

  if (gui->ta.state.linedraw) {
    ansitextview_insert_vt100linedraw_string(gui, pos, text, len);
    return;
  }

  if (!re_compiled) {
    regcomp(&regex,
            "(((https?|ftp)://)|www\\.)[-A-Za-z0-9\\./?=&+%:#_~@,]*[-A-Za-z0-9\\/?=&+%:#_~]",
            REG_EXTENDED | REG_ICASE);
    re_compiled = TRUE;
  }


  memcpy(ctext, text, len);
  ctext[len] = '\0';

  search_start = 0;
  while (search_start < len) {
    if (regexec(&regex, (char *) (ctext + search_start), 1, &match, 0) == 0) {

      ansitextview_append_formatted(gui->txtBuffer,
                                    pos,
                                    (gchar *) (text + search_start),
                                    match.rm_so,
                                    &gui->ta,
                                    NULL);

      ansitextview_append_formatted(gui->txtBuffer,
                                    pos,
                                    (gchar *) (text + search_start + match.rm_so),
                                    match.rm_eo - match.rm_so,
                                    &gui->ta,
                                    gui->txttag_url);

      search_start += match.rm_eo;
    } else {

      ansitextview_append_formatted(gui->txtBuffer,
                                    pos,
                                    (gchar *) (text + search_start),
                                    len - search_start,
                                    &gui->ta,
                                    NULL);
      break;
    }
  }
}
