connectToJid(const Jid &peer, const QString &sid)
{
	close();
	resetConnection(true);

	d->state = Requesting;
	d->peer = peer;
	d->sid = sid;

#ifdef IBB_DEBUG
	qDebug("IBBConnection[%d]: initiating request to %s", d->id, qPrintable(peer.full()));
#endif

	d->j = new JT_IBB(d->m->client()->rootTask());
	connect(d->j, SIGNAL(finished()), SLOT(ibb_finished()));
	d->j->request(d->peer, d->sid);
	d->j->go(true);
}
