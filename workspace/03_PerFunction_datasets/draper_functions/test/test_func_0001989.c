ParseDataObjectTemplate()
{

	std::string name;
	readHeadOfDataObject( &name);


	std::string guid = GetNextToken();


	bool running = true;
	while ( running )
	{
		std::string s = GetNextToken();

		if( s == "}")
			break;

		if( s.length() == 0)
			ThrowException( "Unexpected end of file reached while parsing template definition");
	}
}
