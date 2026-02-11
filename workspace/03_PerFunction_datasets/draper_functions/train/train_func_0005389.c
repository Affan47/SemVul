sp_set_request(const QString &host, Q_UINT16 port, unsigned char cmd1)
{

	QHostAddress addr;
	if(addr.setAddress(host))
		return sp_set_request(addr, port, cmd1);

	Q3CString h = host.utf8();
	h.truncate(255);
	h = QString::fromUtf8(h).utf8();
	int hlen = h.length();

	int at = 0;
	QByteArray a(4);
	a[at++] = 0x05;
	a[at++] = cmd1;
	a[at++] = 0x00;
	a[at++] = 0x03;


	a.resize(at+hlen+1);
	a[at++] = hlen;
	memcpy(a.data() + at, h.data(), hlen);
	at += hlen;


	a.resize(at+2);
	unsigned short p = htons(port);
	memcpy(a.data() + at, &p, 2);

	return a;
}
