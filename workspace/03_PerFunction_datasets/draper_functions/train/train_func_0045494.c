ParseUnknownDataObject()
{

	bool running = true;
	while( running )
	{
		std::string t = GetNextToken();
		if( t.length() == 0)
			ThrowException( "Unexpected end of file while parsing unknown segment.");

		if( t == "{")
			break;
	}

	unsigned int counter = 1;


	while( counter > 0)
	{
		std::string t = GetNextToken();

		if( t.length() == 0)
			ThrowException( "Unexpected end of file while parsing unknown segment.");

		if( t == "{")
			++counter;
		else
		if( t == "}")
			--counter;
	}
}
