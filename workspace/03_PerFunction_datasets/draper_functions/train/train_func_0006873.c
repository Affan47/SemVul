isTagName(std::string s, size_t &n) const
{
	mail::upper(s);

	if (strncmp(s.c_str(), "$LABEL", 6) == 0)
	{
		n=0;

		istringstream i(s.substr(6));

		i >> n;

		if (!i.fail() && !i.bad() &&
		    n < Tags::tags.names.size())
			return true;
	}
	return false;
}
