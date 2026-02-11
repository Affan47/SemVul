games_scores_update_score_name (GamesScores * self, gchar * new_name, gchar * old_name)
{
  GamesScoresPrivate *priv = self->priv;
  GamesScoresCategoryInternal *cat;
  GList *s, *scores_list;
  gint n, place;
  GamesScore *sc;
  GamesScoreValue score;

  g_return_if_fail (self != NULL);

  place = priv->last_score_position;
  score = priv->last_score_value;

  if (place == 0)
    return;

  if (old_name)
      old_name = g_strdup (old_name);
  else
      old_name = g_strdup (g_get_real_name ());

  cat = games_scores_get_current (self);

  scores_list = games_scores_backend_get_scores (cat->backend);

  s = g_list_last (scores_list);
  n = g_list_length (scores_list);


  while ((n >= place) && (s != NULL)) {
    sc = (GamesScore *) (s->data);
    if ((games_score_compare_values (priv->style, sc->value, score) ==
	 0) && (g_utf8_collate (old_name, sc->name) == 0)) {
      g_free (sc->name);
      sc->name = g_strdup (new_name);
    }

    s = g_list_previous (s);
    n--;
  }

  games_scores_backend_set_scores (cat->backend, scores_list);

  g_free (old_name);
}
