xdataElement() const
{
	QDomNode n = queryTag(iq()).firstChild();
	for (; !n.isNull(); n = n.nextSibling()) {
		QDomElement i = n.toElement();
		if (i.isNull())
			continue;

		if (i.attribute("xmlns") == "jabber:x:data")
			return i;
	}

	return QDomElement();
}
