UT_parse_properties(const char * properties,
									std::map<std::string, std::string> & map)
{
	if ( properties == 0)
		return;
	if (*properties == 0)
		return;

	const char * csstr = properties;

	std::string name;
	std::string value;

	bool bSkip = false;

	while (*csstr)
	{
		if (bSkip)
		{
			if (*csstr == ';')
				bSkip = false;
			++csstr;
			continue;
		}
		s_pass_whitespace (csstr);

		const char * name_start = csstr;
		const char * name_end   = s_pass_name (csstr, ':');

		if (*csstr == 0) break;
		if (name_start == name_end)
		{
			bSkip = true;
			continue;
		}
		name.resize(name_end - name_start);
		std::copy(name_start, name_end, name.begin());

		s_pass_whitespace (csstr);
		if (*csstr != ':')
		{
			bSkip = true;
			continue;
		}

		csstr++;
		s_pass_whitespace (csstr);

		if (*csstr == 0)
			break;

		const char * value_start = csstr;
		const char * value_end   = s_pass_value (csstr);

		if (value_start == value_end)
		{
			bSkip = true;
			continue;
		}
		value.resize(value_end - value_start);
		std::copy(value_start, value_end, value.begin());

		map[name] = value;
	}
}
