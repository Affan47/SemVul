__remove_channels (GstCaps * caps)
{
  GstStructure *s;

  gint i, size;

  size = gst_caps_get_size (caps);
  for (i = 0; i < size; i++) {
    s = gst_caps_get_structure (caps, i);
    gst_structure_remove_field (s, "channel-positions");
    gst_structure_remove_field (s, "channels");
  }
}
