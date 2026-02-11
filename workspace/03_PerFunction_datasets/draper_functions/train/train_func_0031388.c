stripComments(std::string& str)
{
	size_t from;
	size_t to;

	while ((from = str.find_first_not_of("+-<>.,[]")) != std::string::npos)
	{
		to = str.find_first_of("+-<>.,[]", from);
		if (to != std::string::npos)
			to -= from;
		str.erase(from, to);
	}
}
