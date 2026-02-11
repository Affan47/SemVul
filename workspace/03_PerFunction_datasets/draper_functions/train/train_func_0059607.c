clutter_score_rewind (ClutterScore *score)
{
  gboolean was_playing;

  g_return_if_fail (CLUTTER_IS_SCORE (score));

  was_playing = clutter_score_is_playing (score);

  clutter_score_stop (score);

  if (was_playing)
    clutter_score_start (score);
}
