get_matching_brace(string const & str, size_t i)
	{
		int count = 1;
		size_t n = str.size();
		while (i < n) {
			i = str.find_first_of("{}", i+1);
			if (i == npos)
				return i;
			if (str[i] == '{')
				++count;
			else
				--count;
			if (count == 0)
				return i;
		}
		return npos;
	}
