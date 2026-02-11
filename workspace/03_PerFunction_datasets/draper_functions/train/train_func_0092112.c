GetPausedFileCount() const
{
	wxMutexLocker lock( m_mutex );

	uint16 count = 0;
	for ( uint16 i = 0; i < m_filelist.size(); i++ ) {
		if ( m_filelist[i]->GetStatus() == PS_PAUSED ) {
			count++;
		}
	}

	return count;
}
