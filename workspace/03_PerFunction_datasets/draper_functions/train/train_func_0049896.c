isSupported(const char *features, const QString &provider)
{
	return isSupported(QString(features).split(',', QString::SkipEmptyParts), provider);
}
