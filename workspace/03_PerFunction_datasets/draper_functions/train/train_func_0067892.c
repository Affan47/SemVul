servicePort(const char *servname, const char *protoname)
{
  struct servent *se = 0L;
#ifndef HAVE_GETSERVBYNAME_R
  QMutexLocker locker(&getXXbyYYmutex);

  se = getservbyname(servname, protoname);

#else
# ifdef USE_OPENBSD
  struct servent servbuf;
  struct servent_data sdata;
  ::memset(&sdata, 0, sizeof sdata);
  if (getservbyname_r(servname, protoname, &servbuf, &sdata) == 0)
    se = &servbuf;
  else
    se = 0;

# else
  size_t buflen = 1024;
  struct servent servbuf;
  char *buf;
  do
    {
      buf = new char[buflen];
#  ifdef Q_OS_SOLARIS
      if ((se = getservbyname_r(servname, protoname, &servbuf, buf, buflen)) && (errno == ERANGE))
#  else
      if (getservbyname_r(servname, protoname, &servbuf, buf, buflen, &se) == ERANGE)
#  endif
	{
          se = 0L;
	  buflen += 1024;
	  delete [] buf;
	}
      else
	break;
    }
  while (se == 0L);
# endif
#endif


  int servport = -1;
  if (se != NULL)
    servport = ntohs(se->s_port);

#ifdef HAVE_GETSERVBYNAME_R
# ifndef USE_OPENBSD
  delete [] buf;
# endif
#endif

  return servport;
}
