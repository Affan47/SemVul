createMappedAddress(const QHostAddress &addr, quint16 port)
{
	QByteArray out;

	if(addr.protocol() == QAbstractSocket::IPv6Protocol)
	{
		out = QByteArray(20, 0);
		out[1] = 0x02;
		Q_IPV6ADDR addr6 = addr.toIPv6Address();
		memcpy(out.data() + 4, addr6.c, 16);
	}
	else if(addr.protocol() == QAbstractSocket::IPv4Protocol)
	{
		out = QByteArray(8, 0);
		out[1] = 0x01;
		write32((quint8 *)out.data() + 4, addr.toIPv4Address());
	}
	else
		Q_ASSERT(0);

	write16((quint8 *)out.data() + 2, port);
	return out;
}
