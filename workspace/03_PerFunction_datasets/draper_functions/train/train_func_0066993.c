collectValues(const QString & family, const QString & prop, QString & value) {
	if (prop.compare("pin spacing", Qt::CaseInsensitive) == 0) {
		QStringList values;
		foreach (QString f, PinSpacings.keys()) {
			values.append(f);
		}
		value = m_pinSpacing;
		return values;
	}

	return Capacitor::collectValues(family, prop, value);
}
