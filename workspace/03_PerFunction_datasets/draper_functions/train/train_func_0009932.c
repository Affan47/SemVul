entry_added (GstIndex * index, GstIndexEntry * entry, gpointer user_data)
{
  GPtrArray *index_stats = (GPtrArray *) user_data;
  GstIndexStats *s;

  switch (entry->type) {
    case GST_INDEX_ENTRY_ID:

      GST_DEBUG_OBJECT (index, "id %d: describes writer %s", entry->id,
          GST_INDEX_ID_DESCRIPTION (entry));
      if (entry->id >= index_stats->len) {
        g_ptr_array_set_size (index_stats, entry->id + 1);
      }
      s = g_new (GstIndexStats, 1);
      s->id = entry->id;
      s->desc = g_strdup (GST_INDEX_ID_DESCRIPTION (entry));
      s->num_frames = s->num_keyframes = s->num_dltframes = 0;
      s->last_keyframe = s->last_dltframe = GST_CLOCK_TIME_NONE;
      s->min_keyframe_gap = s->max_keyframe_gap = s->avg_keyframe_gap =
          GST_CLOCK_TIME_NONE;
      g_ptr_array_index (index_stats, entry->id) = s;
      break;
    case GST_INDEX_ENTRY_FORMAT:

      GST_DEBUG_OBJECT (index, "id %d: registered format %d for %s\n",
          entry->id, GST_INDEX_FORMAT_FORMAT (entry),
          GST_INDEX_FORMAT_KEY (entry));
      break;
    case GST_INDEX_ENTRY_ASSOCIATION:
    {
      gint64 ts;
      GstAssocFlags flags = GST_INDEX_ASSOC_FLAGS (entry);

      s = g_ptr_array_index (index_stats, entry->id);
      gst_index_entry_assoc_map (entry, GST_FORMAT_TIME, &ts);

      if (flags & GST_ASSOCIATION_FLAG_KEY_UNIT) {
        s->num_keyframes++;

        if (GST_CLOCK_TIME_IS_VALID (ts)) {
          if (GST_CLOCK_TIME_IS_VALID (s->last_keyframe)) {
            GstClockTimeDiff d = GST_CLOCK_DIFF (s->last_keyframe, ts);

            if (G_UNLIKELY (d < 0)) {
              GST_WARNING ("received out-of-order keyframe at %"
                  GST_TIME_FORMAT, GST_TIME_ARGS (ts));

              d = GST_CLOCK_DIFF (ts, s->last_keyframe);
            }

            if (GST_CLOCK_TIME_IS_VALID (s->min_keyframe_gap)) {
              if (d < s->min_keyframe_gap)
                s->min_keyframe_gap = d;
            } else {
              s->min_keyframe_gap = d;
            }
            if (GST_CLOCK_TIME_IS_VALID (s->max_keyframe_gap)) {
              if (d > s->max_keyframe_gap)
                s->max_keyframe_gap = d;
            } else {
              s->max_keyframe_gap = d;
            }
            if (GST_CLOCK_TIME_IS_VALID (s->avg_keyframe_gap)) {
              s->avg_keyframe_gap = (d + s->num_frames * s->avg_keyframe_gap) /
                  (s->num_frames + 1);
            } else {
              s->avg_keyframe_gap = d;
            }
          }
          s->last_keyframe = ts;
        }
      }
      if (flags & GST_ASSOCIATION_FLAG_DELTA_UNIT) {
        s->num_dltframes++;
        if (GST_CLOCK_TIME_IS_VALID (ts)) {
          s->last_dltframe = ts;
        }
      }
      s->num_frames++;

      break;
    }
    default:
      break;
  }
}
