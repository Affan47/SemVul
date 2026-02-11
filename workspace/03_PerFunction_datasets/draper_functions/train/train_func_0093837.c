emitForfeit(Chess::Result::Type type, const QString& description)
{
	if (m_forfeited)
		return;

	m_timer->stop();
	if (m_state == Thinking)
		setState(Observing);
	m_forfeited = true;

	Chess::Side winner;
	if (!m_side.isNull())
		winner = m_side.opposite();
	emit forfeit(Chess::Result(type, winner, description));
}
