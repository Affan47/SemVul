gst_rtcp_packet_sdes_copy_entry (GstRTCPPacket * packet,
    GstRTCPSDESType * type, guint8 * len, guint8 ** data)
{
  guint8 *tdata;
  guint8 tlen;

  g_return_val_if_fail (packet != NULL, FALSE);
  g_return_val_if_fail (packet->type == GST_RTCP_TYPE_SDES, FALSE);
  g_return_val_if_fail (packet->rtcp != NULL, FALSE);
  g_return_val_if_fail (packet->rtcp->map.flags & GST_MAP_READ, FALSE);

  if (!gst_rtcp_packet_sdes_get_entry (packet, type, &tlen, &tdata))
    return FALSE;

  if (len)
    *len = tlen;
  if (data)
    *data = (guint8 *) g_strndup ((gchar *) tdata, tlen);

  return TRUE;
}
