set(const std::string& name, const std::string& value)
{
	Iterator it = _map.find(name);
	if (it != _map.end())
		it->second = value;
	else
		_map.insert(HeaderMap::value_type(name, value));
}
