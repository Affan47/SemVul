setColorString(QString colorName, double op) {


	QString colorString = RatsnestColors::wireColor(m_viewID, colorName);
	if (colorString.isEmpty()) {
		colorString = colorName;
	}

	QColor c;
	c.setNamedColor(colorString);
	setColor(c, op);
	m_colorName = colorName;

	QString shadowColorString = RatsnestColors::shadowColor(m_viewID, colorName);
	if (shadowColorString.isEmpty()) {
		shadowColorString = colorString;
	}

	c.setNamedColor(shadowColorString);
	setShadowColor(c);
}
