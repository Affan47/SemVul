gst_element_provide_clock (GstElement * element)
{
  GstClock *result = NULL;
  GstElementClass *oclass;

  g_return_val_if_fail (GST_IS_ELEMENT (element), NULL);

  oclass = GST_ELEMENT_GET_CLASS (element);

  if (oclass->provide_clock)
    result = oclass->provide_clock (element);

  return result;
}
