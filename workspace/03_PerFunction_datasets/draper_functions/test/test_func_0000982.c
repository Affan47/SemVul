Restart()
{
	if (m_innerHashKeyed)
	{
		AccessHash().Restart();
		m_innerHashKeyed = false;
	}
}
