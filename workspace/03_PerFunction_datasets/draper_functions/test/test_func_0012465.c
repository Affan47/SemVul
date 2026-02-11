gst_pad_query_convert (GstPad * pad, GstFormat src_format, gint64 src_val,
    GstFormat dest_format, gint64 * dest_val)
{
  GstQuery *query;
  gboolean ret;

  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);
  g_return_val_if_fail (dest_format != GST_FORMAT_UNDEFINED, FALSE);
  g_return_val_if_fail (dest_val != NULL, FALSE);

  if (dest_format == src_format || src_val == -1) {
    *dest_val = src_val;
    return TRUE;
  }

  query = gst_query_new_convert (src_format, src_val, dest_format);
  if ((ret = gst_pad_query (pad, query)))
    gst_query_parse_convert (query, NULL, NULL, NULL, dest_val);
  gst_query_unref (query);

  return ret;
}
