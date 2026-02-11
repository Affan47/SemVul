quitPlayers()
{
	if (m_quitting)
		return;
	m_quitting = true;

	if (m_playerCount <= 0)
	{
		quit();
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		if (m_player[i] == 0)
			continue;

		connect(m_player[i], SIGNAL(disconnected()),
			this, SLOT(onPlayerQuit()), Qt::QueuedConnection);
		QMetaObject::invokeMethod(m_player[i], "quit", Qt::QueuedConnection);
	}
}
