set(const std::string &attribute, std::string value)
{
	if (value.length())
		_attrs[attribute] = value;
	else
		_attrs.erase(value);
}
