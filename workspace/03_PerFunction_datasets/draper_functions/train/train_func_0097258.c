SendSecureTokenResponse(RTMP *r, AVal *resp)
{
  RTMPPacket packet;
  char pbuf[1024], *pend = pbuf+sizeof(pbuf);

  packet.m_nChannel = 0x03;
  packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
  packet.m_packetType = 0x14;
  packet.m_nInfoField2 = 0;
  packet.m_nInfoField1 = 0;
  packet.m_hasAbsTimestamp = 0;
  packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

  char *enc = packet.m_body;
  enc = AMF_EncodeString(enc, pend, &av_secureTokenResponse);
  enc = AMF_EncodeNumber(enc, pend, 0.0);
  *enc++ = AMF_NULL;
  enc = AMF_EncodeString(enc, pend, resp);
  if (!enc)
    return false;

  packet.m_nBodySize = enc - packet.m_body;

  return RTMP_SendPacket(r, &packet, false);
}
