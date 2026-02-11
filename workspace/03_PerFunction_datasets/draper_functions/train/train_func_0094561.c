connect(const QString& node, const QString& service)
{

  if (m_sockfd == -1 && (d->proxy.family() == AF_UNSPEC ||
			 node.isEmpty() || service.isEmpty()))
    {

      setError(NotSupported);
      return false;
    }

  if (isOpen())
    {

      return true;
    }

  if (m_sockfd == -1)
    {

      if (!KSocketDevice::connect(d->proxy))
	return false;
      KActiveSocketBase::close();


      QString request = QLatin1String("CONNECT %1:%2 HTTP/1.1\r\n"
				      "Cache-Control: no-cache\r\n"
				      "Host: \r\n"
				      "\r\n");
      QString node2 = node;
      if (node.contains(QLatin1Char(':')))
	node2 = QLatin1Char('[') + node + QLatin1Char(']');

      d->request = request.arg(node2).arg(service).toLatin1();
    }

  return parseServerReply();
}
