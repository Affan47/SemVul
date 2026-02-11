hideText(const QString & filename) {
    QString errorStr;
	int errorLine;
	int errorColumn;
    QDomDocument doc;

    QFile file(filename);
	if (!doc.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
        return QByteArray();
    }

    QDomElement root = doc.documentElement();
    hideTextAux(root, false);

    return TextUtils::removeXMLEntities(doc.toString()).toUtf8();
}
