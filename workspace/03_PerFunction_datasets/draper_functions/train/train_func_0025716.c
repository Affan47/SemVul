gst_element_is_indexable (GstElement * element)
{
  gboolean result;

  g_return_val_if_fail (GST_IS_ELEMENT (element), FALSE);

  result = (GST_ELEMENT_GET_CLASS (element)->set_index != NULL);

  return result;
}
