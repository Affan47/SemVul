loadList(QDomElement & list) {
	QString name = list.attribute("name");
	SyntaxerTrieLeaf * stf = new SyntaxerTrieLeaf(name);
	QDomElement item = list.firstChildElement("item");
	while (!item.isNull()) {
		QString text;
		if (TextUtils::findText(item, text)) {
            QString s = text.trimmed();
            m_trieRoot->addString(s, false, stf);
		}
		item = item.nextSiblingElement("item");
	}
}
