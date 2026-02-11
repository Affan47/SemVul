RTMP_ToggleStream(RTMP *r)
{
  int res;

  if (!r->m_pausing)
    {
      if (RTMP_IsTimedout(r) && r->m_read.status == RTMP_READ_EOF)
        r->m_read.status = 0;

      res = RTMP_SendPause(r, TRUE, r->m_pauseStamp);
      if (!res)
	return res;

      r->m_pausing = 1;
      sleep(1);
    }
  res = RTMP_SendPause(r, FALSE, r->m_pauseStamp);
  r->m_pausing = 3;
  return res;
}
