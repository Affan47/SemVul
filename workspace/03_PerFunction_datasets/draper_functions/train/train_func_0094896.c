AddClient( CUpDownClient* toadd )
{

	if ( toadd->GetClientState() == CS_NEW ) {

		toadd->m_clientState = CS_LISTED;


		m_clientList.insert( IDMapPair( toadd->GetUserIDHybrid(), CCLIENTREF(toadd, wxT("CClientList::AddClient m_clientList.insert"))) );


		if ( toadd->GetIP() ) {
			m_ipList.insert( IDMapPair( toadd->GetIP(), CCLIENTREF(toadd, wxT("CClientList::AddClient m_ipList.insert")) ) );
		}


		if ( toadd->HasValidHash() ) {
			m_hashList.insert( HashMapPair( toadd->GetUserHash(), CCLIENTREF(toadd, wxT("CClientList::AddClient m_hashList.insert")) ) );
		}

		toadd->UpdateStats();
	}
}
