getSampleFrequency(void) const
{
	if (m_skip != 0xFFFF)
		return (uint16_t) floor((115200.0 / ((1.0 + (double) m_skip) * (double) m_period))+0.5);
	else
		return (uint16_t) floor((115200.0 / ((double) m_period))+0.5);
}
