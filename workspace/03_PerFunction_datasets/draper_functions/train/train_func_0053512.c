replace_kc_escapes(const gchar *pattern,
                   const gchar *name,
                   const gchar *character)
{
  static GRegex *reKw = NULL;
  static GRegex *reKc = NULL;
  gchar         *tmp1;
  gchar         *tmp2;


  if (!reKw) {
    reKw = g_regex_new("%Kw", 0, 0, NULL);
  }
  if (!reKc) {
    reKc = g_regex_new("%Kc", 0, 0, NULL);
  }


  tmp1 = g_regex_replace_literal(reKw,
                                 pattern, -1,
                                 0,
                                 name,
                                 0, NULL);
  tmp2 = g_regex_replace_literal(reKc,
                                 tmp1, -1,
                                 0,
                                 character,
                                 0, NULL);

  g_free(tmp1);
  return tmp2;
}
