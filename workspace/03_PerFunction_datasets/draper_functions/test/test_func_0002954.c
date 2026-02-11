toString() const
{
	std::string uri;
	if (isRelative())
	{
		encode(_path, RESERVED_PATH, uri);
	}
	else
	{
		uri = _scheme;
		uri += ':';
		std::string auth = getAuthority();
		if (!auth.empty() || _scheme == "file")
		{
			uri.append("//");
			uri.append(auth);
		}
		if (!_path.empty())
		{
			if (!auth.empty() && _path[0] != '/')
				uri += '/';
			encode(_path, RESERVED_PATH, uri);
		}
		else if (!_query.empty() || !_fragment.empty())
		{
			uri += '/';
		}
	}
	if (!_query.empty())
	{
		uri += '?';
		uri.append(_query);
	}
	if (!_fragment.empty())
	{
		uri += '#';
		encode(_fragment, RESERVED_FRAGMENT, uri);
	}
	return uri;
}
