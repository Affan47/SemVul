gst_rtcp_packet_sdes_add_entry (GstRTCPPacket * packet, GstRTCPSDESType type,
    guint8 len, const guint8 * data)
{
  guint8 *bdata;
  guint offset, size, padded;

  g_return_val_if_fail (packet != NULL, FALSE);
  g_return_val_if_fail (packet->type == GST_RTCP_TYPE_SDES, FALSE);
  g_return_val_if_fail (GST_IS_BUFFER (packet->buffer), FALSE);


  bdata = GST_BUFFER_DATA (packet->buffer);
  size = GST_BUFFER_SIZE (packet->buffer);
  bdata += packet->offset;

  offset = packet->item_offset;

  offset += packet->entry_offset;


  padded = (offset + 2 + len + 1 + 3) & ~3;


  if (packet->offset + padded >= size)
    goto no_space;

  bdata[offset] = type;
  bdata[offset + 1] = len;
  memcpy (&bdata[offset + 2], data, len);
  bdata[offset + 2 + len] = 0;


  packet->length = (padded - 4) >> 2;
  bdata[2] = (packet->length) >> 8;
  bdata[3] = (packet->length) & 0xff;


  packet->entry_offset += 2 + len;

  return TRUE;


no_space:
  {
    return FALSE;
  }
}
