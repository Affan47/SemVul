timeline_context_to_layer (GESTimeline * timeline, gint offset)
{
  gboolean ret = TRUE;
  MoveContext *mv_ctx = &timeline->priv->movecontext;


  if (offset != 0 && (offset > 0 || mv_ctx->min_move_layer >= -offset)) {
    GHashTableIter iter;
    GESContainer *key, *value;
    GESLayer *new_layer;
    guint prio;

    mv_ctx->ignore_needs_ctx = TRUE;

    GST_DEBUG ("Moving %d object, offset %d",
        g_hash_table_size (mv_ctx->toplevel_containers), offset);

    g_hash_table_iter_init (&iter, mv_ctx->toplevel_containers);
    while (g_hash_table_iter_next (&iter, (gpointer *) & key,
            (gpointer *) & value)) {

      if (GES_IS_CLIP (value)) {
        prio = ges_clip_get_layer_priority (GES_CLIP (value));


        new_layer =
            GES_LAYER (g_list_nth_data (timeline->layers, prio + offset));

        if (new_layer == NULL) {
          do {
            new_layer = ges_timeline_append_layer (timeline);
          } while (ges_layer_get_priority (new_layer) < prio + offset);
        }

        ret &= ges_clip_move_to_layer (GES_CLIP (key), new_layer);
      } else if (GES_IS_GROUP (value)) {
        guint32 last_prio = _PRIORITY (value) + offset +
            GES_CONTAINER_HEIGHT (value) - 1;

        new_layer = GES_LAYER (g_list_nth_data (timeline->layers, last_prio));

        if (new_layer == NULL) {
          do {
            new_layer = ges_timeline_append_layer (timeline);
          } while (ges_layer_get_priority (new_layer) < last_prio);
        }

        _set_priority0 (GES_TIMELINE_ELEMENT (value),
            _PRIORITY (value) + offset);
      }
    }


    mv_ctx->min_move_layer = mv_ctx->min_move_layer + offset;

    mv_ctx->ignore_needs_ctx = FALSE;
  }

  return ret;
}
