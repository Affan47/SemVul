CompareData()
{
	DBListType::const_iterator valid = m_valid_list.begin();
	for( ; valid != m_valid_list.end(); ++valid ) {


		if( m_compare_list.size() && !m_compare_list.IsSelected(*valid) )
			continue;


		if( m_skip_list.IsSelected(*valid) )
			continue;


		Compare(*valid);
	}
}
