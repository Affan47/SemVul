clutter_score_get_timeline (ClutterScore *score,
                            gulong        id_)
{
  GNode *node;
  ClutterScoreEntry *entry;

  g_return_val_if_fail (CLUTTER_IS_SCORE (score), NULL);
  g_return_val_if_fail (id_ > 0, NULL);

  node = find_entry_by_id (score, id_);
  if (G_UNLIKELY (!node))
    return NULL;

  entry = node->data;

  return entry->timeline;
}
