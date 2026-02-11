getNumber(string const & name) const
{
	FormatList::const_iterator cit =
		find_if(formatlist.begin(), formatlist.end(),
			FormatNamesEqual(name));
	if (cit != formatlist.end())
		return distance(formatlist.begin(), cit);
	else
		return -1;
}
