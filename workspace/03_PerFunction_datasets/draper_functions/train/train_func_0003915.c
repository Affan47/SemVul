forceStrokeWidth(QDomElement & element, double delta, const QString & stroke, bool recurse, bool fill) {
	bool ok;
	double sw = element.attribute("stroke-width").toDouble(&ok);
    if (!ok) sw = 0;

	element.setAttribute("stroke-width", QString::number(qMax(0, sw + delta)));
	element.setAttribute("stroke", stroke);
    if (fill) element.setAttribute("fill", stroke);

    if (recurse) {
	    QDomElement child = element.firstChildElement();
	    while (!child.isNull()) {
		    forceStrokeWidth(child, delta, stroke, recurse, fill);
		    child = child.nextSiblingElement();
	    }
    }
}
