games_score_new (void)
{
  GamesScore *newscore;
  const gchar* name;

  newscore = g_slice_new0 (GamesScore);
  newscore->time = time (NULL);

  name = g_get_real_name ();
  if (name[0] == '\0' || g_utf8_validate (name, -1, NULL) != TRUE) {
    name = g_get_user_name ();
    if (g_utf8_validate (name, -1, NULL) != TRUE) {
      name = "";
    }
  }
  newscore->name = g_strdup (name);

  return newscore;
}
