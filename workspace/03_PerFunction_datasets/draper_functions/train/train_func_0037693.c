gst_raw_parse_class_set_src_pad_template (GstRawParseClass * klass,
    const GstCaps * allowed_caps)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstPadTemplate *pad_template;

  g_return_if_fail (GST_IS_RAW_PARSE_CLASS (klass));
  g_return_if_fail (allowed_caps != NULL);
  g_return_if_fail (GST_IS_CAPS (allowed_caps));

  pad_template =
      gst_pad_template_new ("src", GST_PAD_SRC, GST_PAD_ALWAYS,
      gst_caps_copy (allowed_caps));
  gst_element_class_add_pad_template (element_class, pad_template);
  gst_object_unref (pad_template);
}
