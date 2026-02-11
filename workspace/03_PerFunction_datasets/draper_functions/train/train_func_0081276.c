gotoWrite(void)
{
	if (!m_reading)
		return;

	FSEEK(m_writePos);
	m_reading = false;
}
