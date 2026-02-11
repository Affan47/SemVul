RTMPPacket_Free(RTMPPacket *p)
{
  if (p->m_body)
    {
      free(p->m_body - RTMP_MAX_HEADER_SIZE);
      p->m_body = NULL;
    }
}
