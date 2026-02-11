closeApplication()
{
	if( !pid ||
		!icon->isExclusive() )
		return;

	vector<string> t = icon->getTitle();
	int closed = 0;

	if( !t.empty() )
	{
		vector<string>::iterator it = t.begin();
		vector<string>::iterator end = t.end();

		for( ; it != end; ++it )
		{
			Window w;

			if( !(w = wm.getWindowFromName( *it,
				dock->getCaseSensitive() )) )
				continue;

			wm.closeWindow( w );
			closed++;
		}
	}

	if( t.empty() || !closed )
		kill( pid, SIGTERM );


}
