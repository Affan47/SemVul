updateFromFile( void)
{
    XTRACE();

    const string configFile = getConfigFileName();
    LOG_INFO << "Updating Configuration from : " << configFile << endl;

    if( !ResourceManagerS::instance()->selectResource( configFile))
    {
	string systemConfigFile = "system/config.txt";
	if( !ResourceManagerS::instance()->selectResource( systemConfigFile))
	{
	    LOG_ERROR << "System Config file not found!" << endl;
	    return;
	}
        LOG_WARNING << "Config file [" << configFile
	            << "] not found, using default." << endl;
    }
    ziStream &infile = ResourceManagerS::instance()->getInputStream();

    string line;

    while( !getline( infile, line).eof())
    {


        if( line[0] == '#') continue;

        list<ConfigHandler*>::iterator i;
        for( i=_configHandlerList.begin(); i!=_configHandlerList.end(); i++)
        {
            ConfigHandler *ch = *i;
            ch->handleLine( line);
        }

        Tokenizer  t( line, " \t\n\r=");
        string setKeyname = t.next();
        if( setKeyname == "set")
        {
	    string keyword = t.next();
	    string value = t.next();


	    updateKeyword( keyword, value);
        }
    }
}
