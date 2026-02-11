startTLSClient(XMPP::TLSHandler *t, const QString &server, const QByteArray &spare)
{
	if(!d->active || d->topInProgress || d->haveTLS())
		return;

	SecureLayer *s = new SecureLayer(t);
	s->prebytes = calcPrebytes();
	linkLayer(s);
	d->layers.append(s);
	d->topInProgress = true;


	s->p.tlsHandler->startClient(server);

	insertData(spare);
}
