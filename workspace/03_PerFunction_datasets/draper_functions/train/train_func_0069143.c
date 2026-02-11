gst_base_parse_add_index_entry (GstBaseParse * parse, guint64 offset,
    GstClockTime ts, gboolean key, gboolean force)
{
  gboolean ret = FALSE;
  GstIndexAssociation associations[2];

  GST_LOG_OBJECT (parse, "Adding key=%d index entry %" GST_TIME_FORMAT
      " @ offset 0x%08" G_GINT64_MODIFIER "x", key, GST_TIME_ARGS (ts), offset);

  if (G_LIKELY (!force)) {

    if (!parse->priv->upstream_seekable) {
      GST_DEBUG_OBJECT (parse, "upstream not seekable; discarding");
      goto exit;
    }


    if (parse->priv->index_last_offset >= (gint64) offset) {
      GST_DEBUG_OBJECT (parse, "already have entries up to offset "
          "0x%08" G_GINT64_MODIFIER "x", parse->priv->index_last_offset);
      goto exit;
    }

    if (GST_CLOCK_TIME_IS_VALID (parse->priv->index_last_ts) &&
        GST_CLOCK_DIFF (parse->priv->index_last_ts, ts) <
        parse->priv->idx_interval) {
      GST_DEBUG_OBJECT (parse, "entry too close to last time %" GST_TIME_FORMAT,
          GST_TIME_ARGS (parse->priv->index_last_ts));
      goto exit;
    }


    if (!parse->priv->index_last_valid) {
      GstClockTime prev_ts;

      gst_base_parse_find_offset (parse, ts, TRUE, &prev_ts);
      if (GST_CLOCK_DIFF (prev_ts, ts) < parse->priv->idx_interval) {
        GST_DEBUG_OBJECT (parse,
            "entry too close to existing entry %" GST_TIME_FORMAT,
            GST_TIME_ARGS (prev_ts));
        parse->priv->index_last_offset = offset;
        parse->priv->index_last_ts = ts;
        goto exit;
      }
    }
  }

  associations[0].format = GST_FORMAT_TIME;
  associations[0].value = ts;
  associations[1].format = GST_FORMAT_BYTES;
  associations[1].value = offset;


  GST_BASE_PARSE_INDEX_LOCK (parse);
  gst_index_add_associationv (parse->priv->index, parse->priv->index_id,
      (key) ? GST_ASSOCIATION_FLAG_KEY_UNIT : GST_ASSOCIATION_FLAG_DELTA_UNIT,
      2, (const GstIndexAssociation *) &associations);
  GST_BASE_PARSE_INDEX_UNLOCK (parse);

  if (key) {
    parse->priv->index_last_offset = offset;
    parse->priv->index_last_ts = ts;
  }

  ret = TRUE;

exit:
  return ret;
}
