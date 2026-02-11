buses() {
	QList<Bus *> busList;
	if (m_modelPart == NULL) return busList;

	foreach (Bus * bus, m_modelPart->buses().values()) {
		busList.append(bus);
	}

	return busList;
}
