file_changed (const QString &path)
{
	if (path == m_OSFile.fileName())
	{
		kDebug(m_debugChannel) << "Rereading " << path;
		updateSourceEvent ("dummy");
	}
}
