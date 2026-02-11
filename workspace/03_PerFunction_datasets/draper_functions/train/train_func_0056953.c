Advance( void)
	{
		m_bStillAtTheRoot = FALSE;
		if (m_pvField)
		{
			m_pvField = m_pRecord->next( m_pvField);
			m_uiAbsoluteCursorPosition++;
		}
	}
