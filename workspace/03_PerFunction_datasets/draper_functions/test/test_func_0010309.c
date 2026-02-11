normalizeAttribute(QDomElement & element, const char * attributeName, double num, double denom)
{
    QString attributeValue = element.attribute(attributeName);
    if (attributeValue.isEmpty()) return true;

    bool ok;
	double n = attributeValue.toDouble(&ok) * num / denom;
    if (!ok) {
        QString string;
        QTextStream stream(&string);
        element.save(stream, 0);

    }

	element.setAttribute(attributeName, QString::number(n));
	return ok;
}
