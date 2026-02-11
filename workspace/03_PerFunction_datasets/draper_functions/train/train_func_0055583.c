simulateInsert(UINT8 key[16])
	{
		m_pMutex->lock();
		UINT16 timestamp=(key[14]<<8)|key[15];
		if(timestamp<m_currentClock-1||timestamp>m_currentClock+1)
			{


			}
		t_databaseInfo* aktDB=m_currDatabase;
		if(timestamp>m_currentClock)
			{

			}
		else if(timestamp<m_currentClock)
			{

			}


				aktDB->m_u32Size++;
				m_pMutex->unlock();
				return E_SUCCESS;


	}
