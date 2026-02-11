build_h263_extension (void)
{
  guint8 ext[7];
  GstBuffer *buf;
  AtomInfo *res;


  GST_WRITE_UINT32_LE (ext, 0);

  GST_WRITE_UINT8 (ext + 4, 0);


  GST_WRITE_UINT8 (ext + 5, 10);
  GST_WRITE_UINT8 (ext + 6, 0);

  buf = _gst_buffer_new_wrapped (ext, sizeof (ext), NULL);
  res = build_codec_data_extension (GST_MAKE_FOURCC ('d', '2', '6', '3'), buf);
  gst_buffer_unref (buf);
  return res;
}
