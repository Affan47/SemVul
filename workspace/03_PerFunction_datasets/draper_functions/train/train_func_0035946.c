parseUnix(const std::string& path)
{
	clear();

	std::string::const_iterator it  = path.begin();
	std::string::const_iterator end = path.end();

	if (it != end)
	{
		if (*it == '/')
		{
			_absolute = true; ++it;
		}
		else if (*it == '~')
		{
			++it;
			if (it == end || *it == '/')
			{
				Path cwd(home());
				_dirs = cwd._dirs;
				_absolute = true;
			}
			else --it;
		}

		while (it != end)
		{
			std::string name;
			while (it != end && *it != '/') name += *it++;
			if (it != end)
			{
				if (_dirs.empty())
				{
					if (!name.empty() && *(name.rbegin()) == ':')
						_device.assign(name, 0, name.length() - 1);
					else
						pushDirectory(name);
				}
				else pushDirectory(name);
			}
			else _name = name;
			if (it != end) ++it;
		}
	}
}
