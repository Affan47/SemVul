connectToHost(const QString &proxyHost, int proxyPort, const QString &url)
{
	reset(true);


	if(!proxyHost.isEmpty()) {
		d->host = proxyHost;
		d->port = proxyPort;
		d->url = url;
		d->use_proxy = true;
	}
	else {
		Q3Url u = url;
		d->host = u.host();
		if(u.hasPort())
			d->port = u.port();
		else
			d->port = 80;
		d->url = u.encodedPathAndQuery();
		d->use_proxy = false;
	}

	resetKey();
	bool last;
	QString key = getKey(&last);

#ifdef PROX_DEBUG
	fprintf(stderr, "HttpPoll: Connecting to %s:%d [%s]", d->host.latin1(), d->port, d->url.latin1());
	if(d->user.isEmpty())
		fprintf(stderr, "\n");
	else
		fprintf(stderr, ", auth {%s,%s}\n", d->user.latin1(), d->pass.latin1());
#endif
	QPointer<QObject> self = this;
	syncStarted();
	if(!self)
		return;

	d->state = 1;
	d->http.setAuth(d->user, d->pass);
	d->http.post(d->host, d->port, d->url, makePacket("0", key, "", QByteArray()), d->use_proxy);
}
