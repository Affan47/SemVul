addDocuments(const QString& documents)
{
	QStringList files = documents.split(QLatin1String("\n"), QString::SkipEmptyParts);
	if (!files.isEmpty()) {
		queueDocuments(files);
	}
}
