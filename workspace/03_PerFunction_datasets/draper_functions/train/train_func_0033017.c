gst_rtp_buffer_set_csrc (GstRTPBuffer * rtp, guint8 idx, guint32 csrc)
{
  guint8 *data;

  data = rtp->data[0];

  g_return_if_fail (idx < GST_RTP_HEADER_CSRC_COUNT (data));

  GST_WRITE_UINT32_BE (GST_RTP_HEADER_CSRC_LIST_OFFSET (data, idx), csrc);
}
