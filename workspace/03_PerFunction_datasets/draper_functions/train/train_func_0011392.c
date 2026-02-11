normalize_filename(const std::string& str)
{
	std::string newstring;

	std::string::size_type last_slash = str.find_last_of('/', str.size());
	if ( last_slash == std::string::npos ) newstring = str;
	else newstring = str.substr(last_slash+1);

	for (std::string::iterator i=newstring.begin(), e=newstring.end(); i!=e; ++i)
	{
		if ( *i == '.' ) *i = '_';
	}

	tolower(newstring);

	return newstring;
}
