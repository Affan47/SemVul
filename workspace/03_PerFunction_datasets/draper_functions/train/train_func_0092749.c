getErrorFromElement(const QDomElement &e, const QString &baseNS, int *code, QString *str)
{
	bool found;
	QDomElement tag = findSubTag(e, "error", &found);
	if(!found)
		return;

	XMPP::Stanza::Error err;
	err.fromXml(tag, baseNS);

	if(code)
		*code = err.code();
	if(str) {
		QPair<QString, QString> desc = err.description();
		if (err.text.isEmpty())
			*str = desc.first + ".\n" + desc.second;
		else
			*str = desc.first + ".\n" + desc.second + "\n" + err.text;
	}

}
