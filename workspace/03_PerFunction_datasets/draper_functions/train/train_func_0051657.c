find_string_prefix
	(
	Uc_location& loc,
	const char *text
	)
	{
	int len = strlen(text);

	std::map<std::string, int>::const_iterator exist =
					text_map.lower_bound(text);
	if (exist == text_map.end() ||
	    strncmp(text, (*exist).first.c_str(), len) != 0)
		{
		char *buf = new char[len + 100];
		sprintf(buf, "Prefix '%s' matches no string in this function",
									text);
		loc.error(buf);
		delete buf;
		return 0;
		}
	std::map<std::string, int>::const_iterator next = exist;
	++next;
	if (next != text_map.end() &&
	    strncmp(text, (*next).first.c_str(), len) == 0)
		{
		char *buf = new char[len + 100];
		sprintf(buf, "Prefix '%s' matches more than one string", text);
		loc.error(buf);
		delete buf;
		}
	return (*exist).second;
	}
