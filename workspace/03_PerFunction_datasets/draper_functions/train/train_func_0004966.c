start_tracking_track_element (GESTimeline * timeline,
    GESTrackElement * trackelement)
{
  guint64 *pstart, *pend;
  GSequence *by_layer_sequence;
  TrackObjIters *iters;
  GESTimelinePrivate *priv = timeline->priv;

  guint layer_prio = _ges_track_element_get_layer_priority (trackelement);
  GList *layer_node = g_list_find_custom (timeline->layers,
      GINT_TO_POINTER (layer_prio), (GCompareFunc) find_layer_by_prio);
  GESLayer *layer = layer_node ? layer_node->data : NULL;

  iters = g_slice_new0 (TrackObjIters);


  g_hash_table_insert (priv->obj_iters, trackelement, iters);


  if (G_UNLIKELY (layer == NULL)) {


    GST_ERROR_OBJECT (timeline, "Adding a TrackElement that lands in no layer "
        "we are controlling");
  } else {
    by_layer_sequence = g_hash_table_lookup (priv->by_layer, layer);
    iters->iter_by_layer =
        g_sequence_insert_sorted (by_layer_sequence, trackelement,
        (GCompareDataFunc) element_start_compare, NULL);
    iters->layer = layer;
  }

  if (GES_IS_SOURCE (trackelement)) {

    pstart = g_malloc (sizeof (guint64));
    pend = g_malloc (sizeof (guint64));
    *pstart = _START (trackelement);
    *pend = *pstart + _DURATION (trackelement);

    iters->iter_start = g_sequence_insert_sorted (priv->starts_ends, pstart,
        (GCompareDataFunc) compare_uint64, NULL);
    iters->iter_end = g_sequence_insert_sorted (priv->starts_ends, pend,
        (GCompareDataFunc) compare_uint64, NULL);
    iters->iter_obj =
        g_sequence_insert_sorted (priv->tracksources,
        gst_object_ref (trackelement), (GCompareDataFunc) element_start_compare,
        NULL);
    iters->trackelement = trackelement;

    g_hash_table_insert (priv->by_start, trackelement, pstart);
    g_hash_table_insert (priv->by_object, pstart, trackelement);
    g_hash_table_insert (priv->by_end, trackelement, pend);
    g_hash_table_insert (priv->by_object, pend, trackelement);

    timeline->priv->movecontext.needs_move_ctx = TRUE;

    timeline_update_duration (timeline);
    create_transitions (timeline, trackelement);
  }
}
