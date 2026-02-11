logBinaryMessage(const QByteArray &blob, Severity severity )
{
	if (severity <= level ()) {
		for ( int i = 0; i < m_loggers.size(); ++i )
		{
			m_loggers[i]->logBinaryMessage( blob, severity );
		}
	}
}
