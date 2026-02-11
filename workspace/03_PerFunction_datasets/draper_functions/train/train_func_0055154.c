gst_element_iterate_sink_pads (GstElement * element)
{
  g_return_val_if_fail (GST_IS_ELEMENT (element), NULL);

  return gst_element_iterate_pad_list (element, &element->sinkpads);
}
