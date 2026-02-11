fromXml(const QDomElement &ele)
{
	QDomElement child = ele.firstChildElement();
	while (!child.isNull()) {
		bool isunknown=false;
		QString name = child.nodeName();
		Q_ASSERT(name != "");
		if (!child.hasAttribute("type")) {

			if ( !trees_.contains(name) )
				trees_[name] = new VariantTree(this);
			trees_[name]->fromXml(child);
		}
		else {

			QVariant val;
			val = elementToVariant(child);
			if (val.isValid()) {
				values_[name] = val;
			} else {
				isunknown = true;
				if (!unknownsDoc) unknownsDoc = new QDomDocument();
				QDomDocumentFragment frag(unknownsDoc->createDocumentFragment());
				frag.appendChild(unknownsDoc->importNode(child, true));
				unknowns_[name] = frag;
			}
		}


		if (!isunknown && child.hasAttribute("comment")) {
			QString comment=child.attribute("comment");
			comments_[name]=comment;
		}
		child=child.nextSiblingElement();
	}
}
