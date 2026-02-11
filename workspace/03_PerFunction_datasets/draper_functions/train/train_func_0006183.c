peek_cache (GstMPEGPacketize * packetize, guint length, guint8 ** buf)
{
  *buf = packetize->cache + packetize->cache_head;

  if (packetize->cache_tail - packetize->cache_head < length)
    return packetize->cache_tail - packetize->cache_head;

  return length;
}
