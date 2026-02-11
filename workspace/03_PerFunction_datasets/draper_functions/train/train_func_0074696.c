setScore( int n )
{
	if (n<1000)
		m_score = n;
	else
		m_score = 999;
	emit updateStats();
}
