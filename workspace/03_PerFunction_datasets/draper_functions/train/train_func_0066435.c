replace_all(SCP_string& context, const SCP_string& from, const SCP_string& to)
{
	size_t from_len = from.length();
	size_t to_len = to.length();

	size_t lookHere = 0;
	size_t foundHere;
	while ((foundHere = context.find(from, lookHere)) != SCP_string::npos)
	{
		context.replace(foundHere, from_len, to);
		lookHere = foundHere + to_len;
	}
	return context;
}
