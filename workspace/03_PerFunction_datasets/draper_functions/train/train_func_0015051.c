gst_caps_set_value (GstCaps * caps, const char *field, const GValue * value)
{
  guint i, len;

  g_return_if_fail (GST_IS_CAPS (caps));
  g_return_if_fail (IS_WRITABLE (caps));
  g_return_if_fail (field != NULL);
  g_return_if_fail (G_IS_VALUE (value));

  len = GST_CAPS_LEN (caps);
  for (i = 0; i < len; i++) {
    GstStructure *structure = gst_caps_get_structure_unchecked (caps, i);
    gst_structure_set_value (structure, field, value);
  }
}
