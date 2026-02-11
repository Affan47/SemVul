FillCache()
{


	DatabaseDatabase dbdb = m_dbdb;
	dbdb.SortByRecordCount();


	DatabaseDatabase::DatabaseArrayType::const_iterator
		i = dbdb.Databases.begin(), e = dbdb.Databases.end();
	for( ; i != e; ++i ) {
		if( IsParsable(i->Name) ) try {
			SendStatusEvent(i->Name);
			m_dbmap->LoadDBCache(i->Name);
		} catch( Barry::Error &be ) {
			cerr << be.what() << endl;
		}

		if( m_abort_flag )
			break;
	}

	SendStatusEvent("");


	m_abort_flag = true;
}
