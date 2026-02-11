requestProxyInfo(const Jid &to)
{
	d->mode = 1;

	QDomElement iq;
	d->to = to;
	iq = createIQ(doc(), "get", to.full(), id());
	QDomElement query = doc()->createElement("query");
	query.setAttribute("xmlns", S5B_NS);
	iq.appendChild(query);
	d->iq = iq;
}
