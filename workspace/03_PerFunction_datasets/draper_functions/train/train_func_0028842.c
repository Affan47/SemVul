init()
{
	TRACE("ResourceList::init");

	clear();
	ResourceHandler handler( this );
	QFile file( DATA_PATH + "resources.dat" );
	QXmlInputSource source( &file );
	QXmlSimpleReader reader;
	reader.setContentHandler( &handler );
	reader.setErrorHandler( &handler );
	bool ok = reader.parse( source );
	file.close();
	if ( !ok ) {
		logEE( "Parse Error (%s) : %s", QString( DATA_PATH + "resources.dat" ).toLatin1().constData(), handler.errorProtocol().toLatin1().constData() );
		return false;
	}

	return true;
}
