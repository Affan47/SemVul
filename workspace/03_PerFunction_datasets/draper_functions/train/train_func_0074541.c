translateKey(const std::string& key) const
{
	std::string result(key);
	if (result.compare(0, _toPrefix.size(), _toPrefix) == 0)
		result.replace(0, _toPrefix.size(), _fromPrefix);
	return result;
}
