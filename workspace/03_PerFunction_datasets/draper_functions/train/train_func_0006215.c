id3_mux_render_v1_tag (GstTagMux * mux, const GstTagList * taglist)
{
  GstMapInfo info;
  GstBuffer *buf;
  guint8 *data;
  gboolean wrote_tag = FALSE;
  int i;

  buf = gst_buffer_new_allocate (NULL, ID3_V1_TAG_SIZE, NULL);
  gst_buffer_map (buf, &info, GST_MAP_WRITE);
  data = info.data;
  memset (data, 0, ID3_V1_TAG_SIZE);

  data[0] = 'T';
  data[1] = 'A';
  data[2] = 'G';


  data[127] = 255;

  for (i = 0; i < G_N_ELEMENTS (v1_funcs); i++) {
    v1_funcs[i].func (taglist, v1_funcs[i].gst_tag, data + v1_funcs[i].offset,
        v1_funcs[i].length, &wrote_tag);
  }

  gst_buffer_unmap (buf, &info);

  if (!wrote_tag) {
    GST_WARNING_OBJECT (mux, "no ID3v1 tag written (no suitable tags found)");
    gst_buffer_unref (buf);
    return NULL;
  }

  return buf;
}
