sock_connected()
{
#ifdef PROX_DEBUG
	fprintf(stderr, "HttpConnect: Connected\n");
#endif
	d->inHeader = true;
	d->headerLines.clear();


	QString s;
	s += QString("CONNECT ") + d->real_host + ':' + QString::number(d->real_port) + " HTTP/1.0\r\n";
	if(!d->user.isEmpty()) {
		QString str = d->user + ':' + d->pass;
		s += QString("Proxy-Authorization: Basic ") + QCA::Base64().encodeString(str) + "\r\n";
	}
	s += "Pragma: no-cache\r\n";
	s += "\r\n";

	QByteArray block = s.toUtf8();
	d->toWrite = block.size();
	d->sock.write(block);
}
