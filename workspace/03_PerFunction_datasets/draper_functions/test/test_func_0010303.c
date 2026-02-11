remove(const std::string& lib_name)
{
	if(libraries.find(lib_name) != libraries.end())
		libraries.erase(lib_name);
}
