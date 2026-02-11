gst_rtcp_packet_sr_get_sender_info (GstRTCPPacket * packet, guint32 * ssrc,
    guint64 * ntptime, guint32 * rtptime, guint32 * packet_count,
    guint32 * octet_count)
{
  guint8 *data;

  g_return_if_fail (packet != NULL);
  g_return_if_fail (packet->type == GST_RTCP_TYPE_SR);
  g_return_if_fail (GST_IS_BUFFER (packet->buffer));

  data = GST_BUFFER_DATA (packet->buffer);


  data += packet->offset + 4;
  if (ssrc)
    *ssrc = GST_READ_UINT32_BE (data);
  data += 4;
  if (ntptime)
    *ntptime = GST_READ_UINT64_BE (data);
  data += 8;
  if (rtptime)
    *rtptime = GST_READ_UINT32_BE (data);
  data += 4;
  if (packet_count)
    *packet_count = GST_READ_UINT32_BE (data);
  data += 4;
  if (octet_count)
    *octet_count = GST_READ_UINT32_BE (data);
}
