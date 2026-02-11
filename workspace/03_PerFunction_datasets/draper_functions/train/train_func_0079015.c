toString() const {
	QStringList values;
	for (int i = 0; i < 6; ++i) {
		values.append(QString::number(m_connectors[i]));
	}
	return values.join(",");
}
