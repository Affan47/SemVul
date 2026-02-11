setDeviceVariable(const std::string& dev, const std::string& name, const std::vector<std::string>& values)throw(NutException)
{
	std::string query = "SET VAR " + dev + " " + name;
	for(size_t n=0; n<values.size(); ++n)
	{
		query += " " + escape(values[n]);
	}
	detectError(sendQuery(query));
}
