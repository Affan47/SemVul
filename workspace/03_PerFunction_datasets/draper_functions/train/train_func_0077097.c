isDIP() {
	QString layout = modelPart()->properties().value("layout", "");
	return (layout.indexOf("double", 0, Qt::CaseInsensitive) >= 0);
}
