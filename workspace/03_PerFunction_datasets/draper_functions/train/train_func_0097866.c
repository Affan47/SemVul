FileManagerCallback()
{
	if ( CConfig::Instance()->GetRecreateShareListTime() != 0 )
	{
		if ( m_tCreateShareListTimeout != 0 )
		{
			if ( time(0) > m_tCreateShareListTimeout )
			{
				CreateShareList();

				m_tCreateShareListTimeout = time(0)+CConfig::Instance()->GetRecreateShareListTime()*60*60;
			}
		}
		else
		{
			m_tCreateShareListTimeout = time(0)+CConfig::Instance()->GetRecreateShareListTime()*60*60;
		}
	}
	else
	{
		m_tCreateShareListTimeout = 0;
	}

	return 0;
}
