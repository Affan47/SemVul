showHint()
{
	if (m_availableMoves.isEmpty() || !m_board->selections().isEmpty())
		return;
	const QPoint location = m_availableMoves.value(qrand() % m_availableMoves.size());
	m_board->setSelection(location, true);
	m_gameState->removePoints(3);
}
