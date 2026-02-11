onGo()
{
	Stanza s = m.toStanza(&(client()->stream()));
	QDomElement e = oldStyleNS(s.element());
	send(e);
	setSuccess();
}
