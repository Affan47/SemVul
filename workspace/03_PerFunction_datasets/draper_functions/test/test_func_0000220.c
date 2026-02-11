gst_mve_mux_palette_from_buffer (GstBuffer * buf)
{
  const GstBuffer *palette = NULL;
  GstCaps *caps = GST_BUFFER_CAPS (buf);

  if (caps != NULL) {
    GstStructure *str = gst_caps_get_structure (caps, 0);
    const GValue *pal = gst_structure_get_value (str, "palette_data");

    if (pal != NULL) {
      palette = gst_value_get_buffer (pal);
      if (GST_BUFFER_SIZE (palette) < 256 * 4)
        palette = NULL;
    }
  }
  return palette;
}
