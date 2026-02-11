findConnection(const QString &sid, const Jid &peer) const
{
	foreach(IBBConnection* c, d->activeConns) {
		if(c->sid() == sid && (peer.isEmpty() || c->peer().compare(peer)) )
			return c;
	}
	return 0;
}
