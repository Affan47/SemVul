hackSvg(const QString & svg, const QString & logo)
{
	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument doc;
	if (!doc.setContent(svg, &errorStr, &errorLine, &errorColumn)) return svg;

	QDomElement root = doc.documentElement();
	root.setAttribute("width", QString::number(logo.length() * 0.1) + "in");

	QString viewBox = root.attribute("viewBox");
	QStringList coords = viewBox.split(" ", QString::SkipEmptyParts);
	coords[2] = QString::number(logo.length() * 10);
	root.setAttribute("viewBox", coords.join(" "));

    QStringList exceptions;
	exceptions << "none" << "";
	QString toColor(colorString());
	SvgFileSplitter::changeColors(root, toColor, exceptions);

	QDomNodeList domNodeList = root.elementsByTagName("text");
	for (int i = 0; i < domNodeList.count(); i++) {
		QDomElement node = domNodeList.item(i).toElement();
		if (node.isNull()) continue;

		if (node.attribute("id").compare("label") != 0) continue;

		node.setAttribute("x", QString::number(logo.length() * 5));

		QDomNodeList childList = node.childNodes();
		for (int j = 0; j < childList.count(); j++) {
			QDomNode child = childList.item(i);
			if (child.isText()) {
				child.setNodeValue(logo);

				modelPart()->setLocalProp("width", logo.length() * 0.1 * 25.4);
				QString h = root.attribute("height");
				bool ok;
				modelPart()->setLocalProp("height", TextUtils::convertToInches(h, &ok, false) * 25.4);
                if (!isBottom()) return  doc.toString();
                return flipSvg(doc.toString());
			}
		}
	}

    if (!isBottom()) return svg;

	return flipSvg(svg);
}
