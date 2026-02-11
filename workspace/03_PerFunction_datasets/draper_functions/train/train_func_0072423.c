buildUnix() const
{
	std::string result;
	if (!_device.empty())
	{
		result.append("/");
		result.append(_device);
		result.append(":/");
	}
	else if (_absolute)
	{
		result.append("/");
	}
	for (StringVec::const_iterator it = _dirs.begin(); it != _dirs.end(); ++it)
	{
		result.append(*it);
		result.append("/");
	}
	result.append(_name);
	return result;
}
