respondSuccess(const Jid &to, const QString &id, const QString &streamid)
{
	QDomElement iq = createIQ(doc(), "result", to.full(), id);
	QDomElement query = doc()->createElement("query");
	query.setAttribute("xmlns", "http://jabber.org/protocol/ibb");
	iq.appendChild(query);
	query.appendChild(textTag(doc(), "streamid", streamid));
	send(iq);
}
