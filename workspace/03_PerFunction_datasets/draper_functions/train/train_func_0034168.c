getStrokeWidth(QDomElement & element, double defaultValue)
{
    bool ok;
	double sw = element.attribute("stroke-width").toDouble(&ok);
    if (ok) return sw;

    QString stroke = element.attribute("stroke");
    if (stroke == "none") return 0;

    QDomElement parent = element.parentNode().toElement();
    while (!parent.isNull()) {
        sw = parent.attribute("stroke-width").toDouble(&ok);
        if (ok) return sw;

        stroke = parent.attribute("stroke");
        if (stroke == "none") return 0;

        parent = parent.parentNode().toElement();
    }


    element.setAttribute("stroke-width", defaultValue);
    return defaultValue;


}
