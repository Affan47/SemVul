ReadN(RTMP *r, char *buffer, int n)
{
  int nOriginalSize = n;
  int avail;
  char *ptr;

  r->m_sb.sb_timedout = FALSE;

#ifdef _DEBUG
  memset(buffer, 0, n);
#endif

  ptr = buffer;
  while (n > 0)
    {
      int nBytes = 0, nRead;
      if (r->Link.protocol & RTMP_FEATURE_HTTP)
        {
	  while (!r->m_resplen)
	    {
	      if (r->m_sb.sb_size < 144)
	        {
		  if (!r->m_unackd)
		    HTTP_Post(r, RTMPT_IDLE, "", 1);
		  if (RTMPSockBuf_Fill(&r->m_sb) < 1)
		    {
		      if (!r->m_sb.sb_timedout)
		        RTMP_Close(r);
		      return 0;
		    }
		}
	      HTTP_read(r, 0);
	    }
	  if (r->m_resplen && !r->m_sb.sb_size)
	    RTMPSockBuf_Fill(&r->m_sb);
          avail = r->m_sb.sb_size;
	  if (avail > r->m_resplen)
	    avail = r->m_resplen;
	}
      else
        {
          avail = r->m_sb.sb_size;
	  if (avail == 0)
	    {
	      if (RTMPSockBuf_Fill(&r->m_sb) < 1)
	        {
	          if (!r->m_sb.sb_timedout)
	            RTMP_Close(r);
	          return 0;
		}
	      avail = r->m_sb.sb_size;
	    }
	}
      nRead = ((n < avail) ? n : avail);
      if (nRead > 0)
	{
	  memcpy(ptr, r->m_sb.sb_start, nRead);
	  r->m_sb.sb_start += nRead;
	  r->m_sb.sb_size -= nRead;
	  nBytes = nRead;
	  r->m_nBytesIn += nRead;
	  if (r->m_bSendCounter
	      && r->m_nBytesIn > r->m_nBytesInSent + r->m_nClientBW / 2)
	    SendBytesReceived(r);
	}

#ifdef _DEBUG
      fwrite(ptr, 1, nBytes, netstackdump_read);
#endif

      if (nBytes == 0)
	{
	  RTMP_Log(RTMP_LOGDEBUG, "%s, RTMP socket closed by peer", __FUNCTION__);

	  RTMP_Close(r);
	  break;
	}

      if (r->Link.protocol & RTMP_FEATURE_HTTP)
	r->m_resplen -= nBytes;

#ifdef CRYPTO
      if (r->Link.rc4keyIn)
	{
	  RC4_encrypt(r->Link.rc4keyIn, nBytes, ptr);
	}
#endif

      n -= nBytes;
      ptr += nBytes;
    }

  return nOriginalSize - n;
}
