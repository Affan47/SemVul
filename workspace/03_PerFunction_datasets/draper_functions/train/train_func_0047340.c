makeFlipTextSvg() {
    QByteArray textSvg = this->property("textSvg").toByteArray();

    QDomDocument doc;
    QString errorStr;
	int errorLine;
	int errorColumn;
    if (!doc.setContent(textSvg, &errorStr, &errorLine, &errorColumn)) {
        DebugDialog::debug(QString("unable to parse schematic text: %1 %2 %3:\n%4").arg(errorStr).arg(errorLine).arg(errorColumn).arg(QString(textSvg)));
		return "";
    }

    QDomElement root = doc.documentElement();
    QDomNodeList nodeList = root.elementsByTagName("text");
    QList<QDomElement> texts;
    for (int i = 0; i < nodeList.count(); i++) {
        texts.append(nodeList.at(i).toElement());
    }

    int ix = 0;
    foreach (QDomElement text, texts) {
        QDomElement g = text.ownerDocument().createElement("g");
        text.parentNode().insertAfter(g, text);
        g.appendChild(text);
        QMatrix m = m_textThings[ix++].flipMatrix;
        TextUtils::setSVGTransform(g, m);
    }

    return doc.toString();
}
