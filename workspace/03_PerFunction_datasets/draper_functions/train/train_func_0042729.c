connectToServer(const QString &server)
{
	if(d->mode != Idle)
		return;
	if(server.isEmpty())
		return;

	d->errorCode = 0;
	d->mode = Connecting;
	d->aaaa = true;


	d->server = QUrl::toAce(server);


	if(d->proxy.type() == Proxy::HttpPoll) {


		HttpPoll *s = new HttpPoll;
		d->bs = s;
		connect(s, SIGNAL(connected()), SLOT(bs_connected()));
		connect(s, SIGNAL(syncStarted()), SLOT(http_syncStarted()));
		connect(s, SIGNAL(syncFinished()), SLOT(http_syncFinished()));
		connect(s, SIGNAL(error(int)), SLOT(bs_error(int)));
		if(!d->proxy.user().isEmpty())
			s->setAuth(d->proxy.user(), d->proxy.pass());
		s->setPollInterval(d->proxy.pollInterval());

		if(d->proxy.host().isEmpty())
			s->connectToUrl(d->proxy.url());
		else
			s->connectToHost(d->proxy.host(), d->proxy.port(), d->proxy.url());
	}
	else if (d->proxy.type() == Proxy::HttpConnect) {
		if(!d->opt_host.isEmpty()) {
			d->host = d->opt_host;
			d->port = d->opt_port;
		}
		else {
			d->host = server;
			d->port = 5222;
		}
		do_connect();
	}
	else {
		if(!d->opt_host.isEmpty()) {
			d->host = d->opt_host;
			d->port = d->opt_port;
			do_resolve();
		}
		else {
			d->multi = true;

			QPointer<QObject> self = this;
			srvLookup(d->server);
			if(!self)
				return;

			d->srv.resolveSrvOnly(d->server, "xmpp-client", "tcp");
		}
	}
}
