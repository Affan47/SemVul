getExtension() const
{
	std::string::size_type pos = _name.rfind('.');
	if (pos != std::string::npos)
		return _name.substr(pos + 1);
	else
		return std::string();
}
