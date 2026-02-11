gst_avi_mux_write_tag (const GstTagList * list, const gchar * tag,
    gpointer data)
{
  const struct
  {
    guint32 fcc;
    const gchar *tag;
  } rifftags[] = {
    {
    GST_RIFF_INFO_IARL, GST_TAG_LOCATION}, {
    GST_RIFF_INFO_IART, GST_TAG_ARTIST}, {
    GST_RIFF_INFO_ICMT, GST_TAG_COMMENT}, {
    GST_RIFF_INFO_ICOP, GST_TAG_COPYRIGHT}, {
    GST_RIFF_INFO_ICRD, GST_TAG_DATE}, {
    GST_RIFF_INFO_IGNR, GST_TAG_GENRE}, {
    GST_RIFF_INFO_IKEY, GST_TAG_KEYWORDS}, {
    GST_RIFF_INFO_INAM, GST_TAG_TITLE}, {
    GST_RIFF_INFO_ISFT, GST_TAG_ENCODER}, {
    GST_RIFF_INFO_ISRC, GST_TAG_ISRC}, {
    0, NULL}
  };
  gint n;
  gchar *str;
  GstByteWriter *bw = data;
  guint chunk;

  for (n = 0; rifftags[n].fcc != 0; n++) {
    if (!strcmp (rifftags[n].tag, tag) &&
        gst_tag_list_get_string (list, tag, &str) && str) {
      chunk = gst_avi_mux_start_chunk (bw, NULL, rifftags[n].fcc);
      gst_byte_writer_put_string (bw, str);
      gst_avi_mux_end_chunk (bw, chunk);
      g_free (str);
      break;
    }
  }
}
