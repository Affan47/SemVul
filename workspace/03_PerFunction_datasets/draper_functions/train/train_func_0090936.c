HasContig( const string& name ) const
{
	for(uint32 i = 0 ; i <= m_contigList.size(); i++ )
	{
		if( name == m_contigList[i]->GetName() )
			return true;
	}
	return false;
}
