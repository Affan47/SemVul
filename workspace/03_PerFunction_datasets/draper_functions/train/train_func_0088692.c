bind(const KResolverEntry& address)
{
  resetError();

  if (m_sockfd == -1 && !create(address))
    return false;


  if (kde_bind(m_sockfd, address.address(), address.length()) == -1)
    {
      if (errno == EADDRINUSE)
      {
	setError(AddressInUse);
	return false;
      }
      else if (errno == EINVAL)
	setError(AlreadyBound);
      else
       {
#ifdef Q_WS_WIN
         qDebug(" bind failed: %s ",address.address().toString().toLatin1().constData());
#endif

         setError(NotSupported);
         return false;
       }
    }

  return true;
}
