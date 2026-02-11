hideText3(const QString & svg) {
    QString errorStr;
	int errorLine;
	int errorColumn;
    QDomDocument doc;

	if (!doc.setContent(svg, &errorStr, &errorLine, &errorColumn)) {
        return "";
    }

    QDomElement root = doc.documentElement();
    hideTextAux(root, false);

    return TextUtils::removeXMLEntities(doc.toString());
}
