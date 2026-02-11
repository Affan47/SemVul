connect(const KResolverEntry& address)
{
  resetError();

  if (m_sockfd == -1 && !create(address))
    return false;

  int retval;
  if (KSocks::self()->hasWorkingAsyncConnect())
    retval = KSocks::self()->connect(m_sockfd, address.address(),
				     address.length());
  else
    {


      bool isBlocking = blocking();
      setBlocking(true);
      retval = KSocks::self()->connect(m_sockfd, address.address(),
				       address.length());
      setBlocking(isBlocking);
    }

  if (retval == -1)
    {
      if (errno == EISCONN)
	return true;
      else if (errno == EALREADY || errno == EINPROGRESS)
	{
	  setError(InProgress);
	  return true;
	}
      else if (errno == ECONNREFUSED)
	setError(ConnectionRefused);
      else if (errno == ENETDOWN || errno == ENETUNREACH ||
	       errno == ENETRESET || errno == ECONNABORTED ||
	       errno == ECONNRESET || errno == EHOSTDOWN ||
	       errno == EHOSTUNREACH)
	setError(NetFailure);
      else
	setError(NotSupported);

      return false;
    }

  setOpenMode(ReadWrite | Unbuffered);
  return true;
}
