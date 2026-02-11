findConnection(const QString &sid, const Jid &peer) const
{
	IBBConnectionListIt it(d->activeConns);
	for(IBBConnection *c; (c = it.current()); ++it) {
		if(c->streamid() == sid && (peer.isEmpty() || c->peer().compare(peer)) )
			return c;
	}
	return 0;
}
