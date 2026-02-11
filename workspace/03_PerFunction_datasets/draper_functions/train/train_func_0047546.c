shift(double x, double y, const QString & elementID, bool shiftTransforms)
{
	QDomElement root = m_domDocument.documentElement();

	QDomElement mainElement = TextUtils::findElementWithAttribute(root, "id", elementID);
	if (mainElement.isNull()) return "";

	QDomElement childElement = mainElement.firstChildElement();
	while (!childElement.isNull()) {
		shiftChild(childElement, x, y, shiftTransforms);
		childElement = childElement.nextSiblingElement();
	}

	QDomDocument document;
	QDomNode node = document.importNode(mainElement, true);
	document.appendChild(node);

	return document.toString();

}
