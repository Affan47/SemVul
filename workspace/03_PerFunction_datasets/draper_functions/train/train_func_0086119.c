WriteN(RTMP * r, const char *buffer, int n)
{
  const char *ptr = buffer;

  while (n > 0)
    {
#ifdef _DEBUG
      fwrite(ptr, 1, n, netstackdump);
#endif

      int nBytes = send(r->m_socket, ptr, n, 0);


      if (nBytes < 0)
	{
	  int sockerr = GetSockError();
	  Log(LOGERROR, "%s, RTMP send error %d (%d bytes)", __FUNCTION__,
	      sockerr, n);

	  if (sockerr == EINTR && !RTMP_ctrlC)
	    continue;

	  RTMP_Close(r);
	  n = 1;
	  break;
	}

      if (nBytes == 0)
	break;

      n -= nBytes;
      ptr += nBytes;
    }

  return n == 0;
}
