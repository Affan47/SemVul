WLDGetString( const string &name )
{
	map <string, string>::iterator str_iter;

	if((str_iter = WLDStringStorage.find(name)) != WLDStringStorage.end()   )
		return str_iter->second;

	return WLDEmptyStr;
}
