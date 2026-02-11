_parse_tot (GstMpegTsSection * section)
{
  guint8 *data;
  GstMpegTsTOT *tot;
  guint16 desc_len;

  GST_DEBUG ("TOT");

  tot = g_slice_new0 (GstMpegTsTOT);

  tot->utc_time = _parse_utc_time (section->data + 3);


  data = section->data + 8;

  desc_len = GST_READ_UINT16_BE (data) & 0xFFF;
  data += 2;
  tot->descriptors = gst_mpegts_parse_descriptors (data, desc_len);

  return (gpointer) tot;
}
