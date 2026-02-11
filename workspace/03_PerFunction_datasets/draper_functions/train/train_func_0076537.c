fromXml(const QDomElement &e)
{
	clear();

	for(QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
		QDomElement i = n.toElement();
		if(i.isNull())
			continue;
		if(i.tagName() == "item") {
			QString var, val;
			var = i.attribute("name");
			QDomText t = i.firstChild().toText();
			if(!t.isNull())
				val = t.data();
			set(var, val);
		}
	}
}
