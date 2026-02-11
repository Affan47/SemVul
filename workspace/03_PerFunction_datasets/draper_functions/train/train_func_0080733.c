respondSuccess(const Jid &to, const QString &id, const Jid &streamHost)
{
	QDomElement iq = createIQ(doc(), "result", to.full(), id);
	QDomElement query = doc()->createElement("query");
	query.setAttribute("xmlns", "http://jabber.org/protocol/bytestreams");
	iq.appendChild(query);
	QDomElement shost = doc()->createElement("streamhost-used");
	shost.setAttribute("jid", streamHost.full());
	query.appendChild(shost);
	send(iq);
}
