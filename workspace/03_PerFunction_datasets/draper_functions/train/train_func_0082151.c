gst_aiff_parse_read_chunk (GstAiffParse * aiff, guint64 * offset, guint32 * tag,
    GstBuffer ** data)
{
  guint size;
  GstFlowReturn res;
  GstBuffer *buf;

  if ((res =
          gst_pad_pull_range (aiff->sinkpad, *offset, 8, &buf)) != GST_FLOW_OK)
    return res;

  *tag = GST_READ_UINT32_LE (GST_BUFFER_DATA (buf));
  size = GST_READ_UINT32_BE (GST_BUFFER_DATA (buf) + 4);

  if ((res =
          gst_pad_pull_range (aiff->sinkpad, (*offset) + 8, size,
              &buf)) != GST_FLOW_OK)
    return res;
  else if (GST_BUFFER_SIZE (buf) < size)
    goto too_small;

  *data = buf;
  *offset += 8 + GST_ROUND_UP_2 (size);

  return GST_FLOW_OK;


too_small:
  {

    GST_DEBUG_OBJECT (aiff, "not enough data (available=%u, needed=%u)",
        GST_BUFFER_SIZE (buf), size);
    gst_buffer_unref (buf);
    return GST_FLOW_UNEXPECTED;
  }

}
