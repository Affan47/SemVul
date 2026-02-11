gst_element_set_base_time (GstElement * element, GstClockTime time)
{
  GstClockTime old;

  g_return_if_fail (GST_IS_ELEMENT (element));

  GST_OBJECT_LOCK (element);
  old = element->base_time;
  element->base_time = time;
  GST_OBJECT_UNLOCK (element);

  GST_CAT_DEBUG_OBJECT (GST_CAT_CLOCK, element,
      "set base_time=%" GST_TIME_FORMAT ", old %" GST_TIME_FORMAT,
      GST_TIME_ARGS (time), GST_TIME_ARGS (old));
}
