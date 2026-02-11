takeIncoming()
{
	if(d->incomingConns.isEmpty())
		return 0;

	SocksClient *c = d->incomingConns.getFirst();
	d->incomingConns.removeRef(c);


	disconnect(c, SIGNAL(error(int)), this, SLOT(connectionError()));


	QTimer::singleShot(0, c, SLOT(serve()));

	return c;
}
