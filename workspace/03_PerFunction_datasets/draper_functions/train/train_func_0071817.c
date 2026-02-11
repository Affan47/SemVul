read_cache (GstMPEGPacketize * packetize, guint length, GstBuffer ** outbuf)
{
  if (packetize->cache_tail - packetize->cache_head < length)
    return GST_FLOW_RESEND;
  if (length == 0)
    return GST_FLOW_RESEND;

  *outbuf = gst_buffer_new_and_alloc (length);

  memcpy (GST_BUFFER_DATA (*outbuf), packetize->cache + packetize->cache_head,
      length);
  packetize->cache_head += length;

  return GST_FLOW_OK;
}
