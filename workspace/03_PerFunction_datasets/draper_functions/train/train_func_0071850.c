strtolower(std::string& str)
{
    for(std::string::iterator i = str.begin();
	i != str.end();
	i++ )
	*i = tolower( *i );

    return str;
}
