gst_camerabin_setup_default_element (GstBin * bin, GstElement * user_elem,
    const gchar * auto_elem_name, const gchar * default_elem_name,
    const gchar * instance_name)
{
  GstElement *elem;

  if (user_elem) {
    GST_DEBUG_OBJECT (bin, "trying configured element");
    elem = try_element (GST_ELEMENT_CAST (bin), gst_object_ref (user_elem));
  } else {

    GST_DEBUG_OBJECT (bin, "trying %s", auto_elem_name);
    elem = gst_element_factory_make (auto_elem_name, instance_name);
    elem = try_element (GST_ELEMENT_CAST (bin), elem);
    if (elem == NULL) {

      if (strcmp (default_elem_name, auto_elem_name)) {
        GST_DEBUG_OBJECT (bin, "trying %s", default_elem_name);
        elem = gst_element_factory_make (default_elem_name, instance_name);
        elem = try_element (GST_ELEMENT_CAST (bin), elem);
      }
    }
  }
  return elem;
}
