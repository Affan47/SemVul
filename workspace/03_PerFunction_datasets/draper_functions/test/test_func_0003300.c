sendStreamError(int cond, const QString &text, const QDomElement &appSpec)
{
	QDomElement se = doc.createElementNS(NS_ETHERX, "stream:error");
	QDomElement err = doc.createElementNS(NS_STREAMS, streamCondToString(cond));
	if(!otherHost.isEmpty())
		err.appendChild(doc.createTextNode(otherHost));
	se.appendChild(err);
	if(!text.isEmpty()) {
		QDomElement te = doc.createElementNS(NS_STREAMS, "text");
		te.setAttributeNS(NS_XML, "xml:lang", "en");
		te.appendChild(doc.createTextNode(text));
		se.appendChild(te);
	}
	se.appendChild(appSpec);

	writeElement(se, 100, false);
}
