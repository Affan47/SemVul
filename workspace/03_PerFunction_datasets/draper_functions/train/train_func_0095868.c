fromXml(const QDomElement& e)
{
	setJid(e.attribute("jid"));
	setName(e.attribute("name"));
	if (e.attribute("action") == "delete") {
		setAction(Delete);
	}
	else if (e.attribute("action") == "modify") {
		setAction(Modify);
	}
	else {
		setAction(Add);
	}
	QDomNodeList nl = e.childNodes();
	for(int n = 0; n < nl.count(); ++n) {
		QDomElement g = nl.item(n).toElement();
		if (!g.isNull() && g.tagName() == "group") {
			groups_ += g.text();
		}
	}
}
