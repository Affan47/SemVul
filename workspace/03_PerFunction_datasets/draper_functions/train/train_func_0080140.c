findText(const QDomNode & node, QString & text) {
	if (node.isText()) {
		text = node.nodeValue();
		return true;
	}

	QDomNode cnode = node.firstChild();
	while (!cnode.isNull()) {
		if (findText(cnode, text)) return true;

		cnode = cnode.nextSibling();
	}

	return false;
}
