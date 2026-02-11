gst_insert_bin_insert_after (GstInsertBin * self, GstElement * element,
    GstElement * sibling, GstInsertBinCallback callback, gpointer user_data)
{
  g_return_if_fail (GST_IS_ELEMENT (element));
  g_return_if_fail (GST_IS_ELEMENT (sibling));

  gst_insert_bin_add (self, element, sibling, DIRECTION_AFTER,
      callback, user_data);
}
