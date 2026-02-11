allScores() const
{
	bool all;
	all = true;
	for (int i = 0; i < m_players.count(); i++) all = all && m_players.at(i).allScores();
	return all;
}
