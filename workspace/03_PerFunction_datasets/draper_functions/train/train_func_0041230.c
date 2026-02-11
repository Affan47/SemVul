gst_tag_mux_adjust_event_offsets (GstTagMux * mux,
    const GstEvent * newsegment_event)
{
  GstFormat format;
  gint64 start, stop, cur;

  gst_event_parse_new_segment ((GstEvent *) newsegment_event, NULL, NULL,
      &format, &start, &stop, &cur);

  g_assert (format == GST_FORMAT_BYTES);

  if (start != -1)
    start += mux->priv->start_tag_size;
  if (stop != -1)
    stop += mux->priv->start_tag_size;
  if (cur != -1)
    cur += mux->priv->start_tag_size;

  GST_DEBUG_OBJECT (mux, "adjusting newsegment event offsets to start=%"
      G_GINT64_FORMAT ", stop=%" G_GINT64_FORMAT ", cur=%" G_GINT64_FORMAT
      " (delta = +%" G_GSIZE_FORMAT ")", start, stop, cur,
      mux->priv->start_tag_size);

  return gst_event_new_new_segment (TRUE, 1.0, format, start, stop, cur);
}
