handleHeaderPrefix(const std::string& name, const std::string& value)
	{
		_headerPrefix = value;
		if (!_headerPrefix.empty() && _headerPrefix[_headerPrefix.size() - 1] != '/')
			_headerPrefix += '/';
	}
