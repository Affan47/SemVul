sock_connected()
{
#ifdef PROX_DEBUG
	fprintf(stderr, "HttpProxyPost: Connected\n");
#endif
	d->inHeader = true;
	d->headerLines.clear();

	QUrl u = d->url;


	QString s;
	s += QString("POST ") + d->url + " HTTP/1.0\r\n";
	if(d->asProxy) {
		if(!d->user.isEmpty()) {
			QString str = d->user + ':' + d->pass;
			s += QString("Proxy-Authorization: Basic ") + QCA::Base64().encodeString(str) + "\r\n";
		}
		s += "Pragma: no-cache\r\n";
		s += QString("Host: ") + u.host() + "\r\n";
	}
	else {
		s += QString("Host: ") + d->host + "\r\n";
	}
	s += "Content-Type: application/x-www-form-urlencoded\r\n";
	s += QString("Content-Length: ") + QString::number(d->postdata.size()) + "\r\n";
	s += "\r\n";


	d->sock.write(s.toUtf8());


	d->sock.write(d->postdata);
}
