reset_degree (GstElement * element, GstBinSortIterator * bit)
{
  gboolean is_sink;


  GST_OBJECT_LOCK (element);
  is_sink = GST_OBJECT_FLAG_IS_SET (element, GST_ELEMENT_FLAG_SINK);
  GST_OBJECT_UNLOCK (element);

  if (is_sink) {
    add_to_queue (bit, element);
  } else {

    HASH_SET_DEGREE (bit, element, 0);
  }
}
