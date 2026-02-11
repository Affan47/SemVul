start_entry (ClutterScoreEntry *entry)
{
  ClutterScorePrivate *priv = entry->score->priv;


  if (clutter_timeline_is_playing (entry->timeline))
    return;

  entry->complete_id = g_signal_connect (entry->timeline,
                                         "completed",
                                         G_CALLBACK (on_timeline_completed),
                                         entry);

  CLUTTER_NOTE (SCHEDULER, "timeline [%p] ('%lu') started",
                entry->timeline,
                entry->id);

  if (G_UNLIKELY (priv->running_timelines == NULL))
    priv->running_timelines = g_hash_table_new (NULL, NULL);

  g_hash_table_insert (priv->running_timelines,
                       GUINT_TO_POINTER (entry->id),
                       entry);

  clutter_timeline_start (entry->timeline);

  g_signal_emit (entry->score, score_signals[TIMELINE_STARTED], 0,
                 entry->timeline);
}
