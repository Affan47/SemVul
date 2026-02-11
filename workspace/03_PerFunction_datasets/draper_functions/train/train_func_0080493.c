GetCurTimeAndCleanUp()
{
	if (!m_maxBytesPerSecond)
		return 0;

	double curTime = m_timer.ElapsedTimeAsDouble();
	while (m_ops.size() && (m_ops.front().first + 1000 < curTime))
		m_ops.pop_front();
	return curTime;
}
