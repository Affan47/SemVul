ClientStateChanged( int oldState, int newState )
{
	if ( oldState == newState )
		return;


	if ( oldState != -1 ) {

		if ( oldState == DS_ONQUEUE || oldState == DS_DOWNLOADING ) {
			m_validSources--;
		} else {
			if ( oldState == DS_CONNECTED  ) {
				m_validSources--;
			}

			m_notCurrentSources--;
		}
	}


	if ( newState != -1 ) {

		if ( newState == DS_ONQUEUE || newState == DS_DOWNLOADING ) {
			++m_validSources;
		} else {
			if ( newState == DS_CONNECTED  ) {
				++m_validSources;
			}

			++m_notCurrentSources;
		}
	}
}
