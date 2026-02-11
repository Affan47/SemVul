resolve(const URI& relativeURI)
{
	if (!relativeURI._scheme.empty())
	{
		_scheme   = relativeURI._scheme;
		_userInfo = relativeURI._userInfo;
		_host     = relativeURI._host;
		_port     = relativeURI._port;
		_path     = relativeURI._path;
		_query    = relativeURI._query;
		removeDotSegments();
	}
	else
	{
		if (!relativeURI._host.empty())
		{
			_userInfo = relativeURI._userInfo;
			_host     = relativeURI._host;
			_port     = relativeURI._port;
			_path     = relativeURI._path;
			_query    = relativeURI._query;
			removeDotSegments();
		}
		else
		{
			if (relativeURI._path.empty())
			{
				if (!relativeURI._query.empty())
					_query = relativeURI._query;
			}
			else
			{
				if (relativeURI._path[0] == '/')
				{
					_path = relativeURI._path;
					removeDotSegments();
				}
				else
				{
					mergePath(relativeURI._path);
				}
				_query = relativeURI._query;
			}
		}
	}
	_fragment = relativeURI._fragment;
}
