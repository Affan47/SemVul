compare_interface (GstElement * element, gpointer interface)
{
  GType interface_type = (GType) interface;
  gint ret;

  if (G_TYPE_CHECK_INSTANCE_TYPE (element, interface_type)) {
    ret = 0;
  } else {


    gst_object_unref (element);
    ret = 1;
  }
  return ret;
}
