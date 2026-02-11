bin_query_duration_fold (const GValue * vitem, GValue * ret, QueryFold * fold)
{
  gboolean res = FALSE;
  GstObject *item = g_value_get_object (vitem);
  if (GST_IS_PAD (item))
    res = gst_pad_query (GST_PAD (item), fold->query);
  else
    res = gst_element_query (GST_ELEMENT (item), fold->query);

  if (res) {
    gint64 duration;

    g_value_set_boolean (ret, TRUE);

    gst_query_parse_duration (fold->query, NULL, &duration);

    GST_DEBUG_OBJECT (item, "got duration %" G_GINT64_FORMAT, duration);

    if (duration == -1) {

      fold->max = -1;
      return FALSE;
    }

    if (duration > fold->max)
      fold->max = duration;
  }

  return TRUE;
}
