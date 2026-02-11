apply()
{
	if (!wasChanged()) {
		emit done(0);
		return true;
	}

	if (m_step != 0)
		return false;

	m_step = 0;
	m_failed = 0;

	nextStep(0);

	return true;
}
