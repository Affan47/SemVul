get_matching_brace_back(string const & str, size_t i)
	{
		int count = 1;
		while (i > 0) {
			i = str.find_last_of("{}", i-1);
			if (i == npos)
				return i;
			if (str[i] == '}')
				++count;
			else
				--count;
			if (count == 0)
				return i;
		}
		return npos;
	}
