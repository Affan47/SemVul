mimeIsAction(const QMimeData* m, const QString& action) {
	if(m) {
		QStringList formats = m->formats();
		return formats.contains("action") && (m->data("action") == action);
	} else {
		return false;
	}
}
