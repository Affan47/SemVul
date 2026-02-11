OnInit()
{
	cerr << "OnInit()" << endl;


	try {
		if( g_argv_version == "0.22" )
			m_engine.reset( new OpenSync::OpenSync22 );
		else {
			m_engine.reset( new OpenSync::OpenSync40 );
		}
	}
	catch( std::exception &e ) {
		cerr << e.what() << endl;
		return false;
	}

	if( !m_engine.get() ) {
		cerr << "Unknown engine number: " << g_argv_version << endl;
		return false;
	}


	try {
		m_engine->Discover(g_argv_group_name);
		m_engine->Sync(g_argv_group_name, *this, g_sync_types);
	}
	catch( std::exception &e ) {
		cerr << e.what() << endl;
		return true;
	}

	return true;
}
