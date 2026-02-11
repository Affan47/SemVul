gst_riff_parse_file_header (GstElement * element,
    GstBuffer * buf, guint32 * doctype)
{
  GstMapInfo info;
  guint32 tag;

  g_return_val_if_fail (buf != NULL, FALSE);
  g_return_val_if_fail (doctype != NULL, FALSE);

  gst_buffer_map (buf, &info, GST_MAP_READ);
  if (info.size < 12)
    goto too_small;

  tag = GST_READ_UINT32_LE (info.data);
  if (tag != GST_RIFF_TAG_RIFF && tag != GST_RIFF_TAG_AVF0)
    goto not_riff;

  *doctype = GST_READ_UINT32_LE (info.data + 8);
  gst_buffer_unmap (buf, &info);

  gst_buffer_unref (buf);

  return TRUE;


too_small:
  {
    GST_ELEMENT_ERROR (element, STREAM, WRONG_TYPE, (NULL),
        ("Not enough data to parse RIFF header (%" G_GSIZE_FORMAT " available,"
            " %d needed)", info.size, 12));
    gst_buffer_unmap (buf, &info);
    gst_buffer_unref (buf);
    return FALSE;
  }
not_riff:
  {
    GST_ELEMENT_ERROR (element, STREAM, WRONG_TYPE, (NULL),
        ("Stream is no RIFF stream: %" GST_FOURCC_FORMAT,
            GST_FOURCC_ARGS (tag)));
    gst_buffer_unmap (buf, &info);
    gst_buffer_unref (buf);
    return FALSE;
  }
}
