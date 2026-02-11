gst_element_class_set_documentation_uri (GstElementClass * klass,
    const gchar * uri)
{
  g_return_if_fail (GST_IS_ELEMENT_CLASS (klass));

  gst_element_class_add_meta_data (klass, "doc-uri", uri);
}
