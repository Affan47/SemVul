take(const QDomElement &e)
{
	if(e.tagName() != "message")
		return false;

	Stanza s = client()->stream().createStanza(addCorrectNS(e));
	if(s.isNull()) {

		return false;
	}

	Message m;
	if(!m.fromStanza(s, client()->timeZoneOffset())) {

		return false;
	}

	message(m);
	return true;
}
