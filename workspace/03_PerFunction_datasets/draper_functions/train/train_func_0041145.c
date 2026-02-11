UpdatePartsFrequency( CUpDownClient* client, bool increment )
{


	const BitVector& freq = client->GetPartStatus();

	if ( m_SrcpartFrequency.size() != GetPartCount() ) {
		m_SrcpartFrequency.clear();
		m_SrcpartFrequency.insert(m_SrcpartFrequency.begin(), GetPartCount(), 0);

		if ( !increment ) {
			return;
		}
	}

	unsigned int size = freq.size();
	if ( size != m_SrcpartFrequency.size() ) {
		return;
	}

	if ( increment ) {
		for ( unsigned int i = 0; i < size; i++ ) {
			if ( freq.get(i) ) {
				m_SrcpartFrequency[i]++;
			}
		}
	} else {
		for ( unsigned int i = 0; i < size; i++ ) {
			if ( freq.get(i) ) {
				m_SrcpartFrequency[i]--;
			}
		}
	}
}
