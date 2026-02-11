FindClientByIP( uint32 clientip, uint16 port )
{

	std::pair<IDMap::iterator, IDMap::iterator> range = m_ipList.equal_range( clientip );

	for ( ; range.first != range.second; ++range.first ) {
		CUpDownClient* cur_client = range.first->second.GetClient();

		if ( cur_client->GetUserPort() == port ) {
			return cur_client;
		}
	}

	return NULL;
}
