TimeToNextTransceive()
{
	if (!m_maxBytesPerSecond)
		return 0;

	if (!m_nextTransceiveTime)
		ComputeNextTransceiveTime();

	return SaturatingSubtract(m_nextTransceiveTime, m_timer.ElapsedTimeAsDouble());
}
