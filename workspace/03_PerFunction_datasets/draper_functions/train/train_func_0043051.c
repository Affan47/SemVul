initialize()
{
	if (m_engines.size() < 2)
	{
		qWarning() << "Two engines are needed";
		return false;
	}

	m_fcp = &m_engines[0];
	m_scp = &m_engines[1];
	m_finishing = false;
	m_currentGame = 0;
	m_finishedGames = 0;
	m_drawCount = 0;
	m_games.clear();

	QVector<EngineData>::iterator it;

	if (m_fcp->bookFile == m_scp->bookFile
	&&  !m_fcp->bookFile.isEmpty())
	{
		if (!loadOpeningBook(m_fcp->bookFile, &m_fcp->book))
			return false;
		m_scp->book = m_fcp->book;
	}
	else
	{
		for (it = m_engines.begin(); it != m_engines.end(); ++it)
		{
			if (it->bookFile.isEmpty())
				continue;
			if (!loadOpeningBook(it->bookFile, &it->book))
				return false;
		}
	}

	for (it = m_engines.begin(); it != m_engines.end(); ++it)
	{
		if (!it->tc.isValid())
		{
			qWarning() << "Invalid or missing time control";
			return false;
		}
		if (it->config.protocol().isEmpty())
		{
			qWarning() << "Missing chess protocol";
			return false;
		}

		it->wins = 0;
		it->builder = new EngineBuilder(it->config);
		m_builders << it->builder;
	}

	connect(&m_manager, SIGNAL(ready()), this, SLOT(onManagerReady()));
	connect(&m_manager, SIGNAL(finished()), this, SIGNAL(finished()),
		Qt::QueuedConnection);

	if (m_debug)
		connect(&m_manager, SIGNAL(debugMessage(QString)),
			this, SLOT(print(QString)));

	return true;
}
