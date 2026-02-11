GetSource( uint32 i ) const{
	if( i < m_sourceList.size() ){
		return *(m_sourceList.begin() + i);
	}
	return 0;
}
