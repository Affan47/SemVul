stop_tracking_track_element (GESTimeline * timeline,
    GESTrackElement * trackelement)
{
  guint64 *start, *end;
  TrackObjIters *iters;
  GESTimelinePrivate *priv = timeline->priv;

  iters = g_hash_table_lookup (priv->obj_iters, trackelement);
  if (G_LIKELY (iters->iter_by_layer)) {
    g_sequence_remove (iters->iter_by_layer);
  } else {
    GST_WARNING_OBJECT (timeline, "TrackElement %p was in no layer",
        trackelement);
  }

  if (GES_IS_SOURCE (trackelement)) {
    start = g_hash_table_lookup (priv->by_start, trackelement);
    end = g_hash_table_lookup (priv->by_end, trackelement);

    g_hash_table_remove (priv->by_start, trackelement);
    g_hash_table_remove (priv->by_end, trackelement);
    g_hash_table_remove (priv->by_object, end);
    g_hash_table_remove (priv->by_object, start);
    g_sequence_remove (iters->iter_start);
    g_sequence_remove (iters->iter_end);
    g_sequence_remove (iters->iter_obj);
    timeline_update_duration (timeline);
  }
  g_hash_table_remove (priv->obj_iters, trackelement);
}
