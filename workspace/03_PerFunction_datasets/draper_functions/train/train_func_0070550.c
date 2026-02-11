gst_rtcp_packet_get_rb (GstRTCPPacket * packet, guint nth, guint32 * ssrc,
    guint8 * fractionlost, gint32 * packetslost, guint32 * exthighestseq,
    guint32 * jitter, guint32 * lsr, guint32 * dlsr)
{
  guint8 *data;
  guint32 tmp;

  g_return_if_fail (packet != NULL);
  g_return_if_fail (packet->type == GST_RTCP_TYPE_RR ||
      packet->type == GST_RTCP_TYPE_SR);
  g_return_if_fail (GST_IS_BUFFER (packet->buffer));

  data = GST_BUFFER_DATA (packet->buffer);


  data += packet->offset + 4;
  if (packet->type == GST_RTCP_TYPE_RR)
    data += 4;
  else
    data += 24;


  data += (nth * 24);

  if (ssrc)
    *ssrc = GST_READ_UINT32_BE (data);
  data += 4;
  tmp = GST_READ_UINT32_BE (data);
  if (fractionlost)
    *fractionlost = (tmp >> 24);
  if (packetslost) {

    if (tmp & 0x00800000)
      tmp |= 0xff000000;
    else
      tmp &= 0x00ffffff;
    *packetslost = (gint32) tmp;
  }
  data += 4;
  if (exthighestseq)
    *exthighestseq = GST_READ_UINT32_BE (data);
  data += 4;
  if (jitter)
    *jitter = GST_READ_UINT32_BE (data);
  data += 4;
  if (lsr)
    *lsr = GST_READ_UINT32_BE (data);
  data += 4;
  if (dlsr)
    *dlsr = GST_READ_UINT32_BE (data);
}
