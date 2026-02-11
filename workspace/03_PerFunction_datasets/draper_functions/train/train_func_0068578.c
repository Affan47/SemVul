shootRay( int borderPosition )
{
	int outgoingBorderPosition = m_balls->oppositeBorderPosition(borderPosition);

	if ((outgoingBorderPosition == HIT_POSITION) || (borderPosition == outgoingBorderPosition))
		setScore(m_score + SCORE_ONE);
	else
		setScore(m_score + SCORE_TWO);

	if (!m_tutorial->isVisible())
		setRunning(true);
	emit updateStats();

	return outgoingBorderPosition;
}
