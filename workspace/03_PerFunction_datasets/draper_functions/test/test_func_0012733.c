find_color_balance_element (GstElement * element)
{
  GstIterator *it;
  GstColorBalance *cb = NULL;

  if (GST_IS_COLOR_BALANCE (element)
      && is_valid_color_balance_element (GST_COLOR_BALANCE (element)))
    return GST_COLOR_BALANCE (gst_object_ref (element));
  else if (!GST_IS_BIN (element))
    return FALSE;

  it = gst_bin_iterate_all_by_interface (GST_BIN (element),
      GST_TYPE_COLOR_BALANCE);
  while (gst_iterator_foreach (it, iterate_color_balance_elements,
          &cb) == GST_ITERATOR_RESYNC)
    gst_iterator_resync (it);
  gst_iterator_free (it);

  return cb;
}
