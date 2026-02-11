isAcceptableSID(const Jid &peer, const QString &sid) const
{
	QString key = makeKey(sid, d->client->jid(), peer);
	QString key_out = makeKey(sid, peer, d->client->jid());


	if(d->serv) {
		if(findServerEntryByHash(key) || findServerEntryByHash(key_out))
			return false;
	}
	else {
		if(findEntryByHash(key) || findEntryByHash(key_out))
			return false;
	}
	return true;
}
