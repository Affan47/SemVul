exists(string name) const
{
	mail::upper(name);

	const_iterator b, e;

	b=begin();
	e=end();

	size_t s=name.size();

	while (b != e)
	{
		if (b->first == name)
			return true;

		if (b->first.size() > s &&
		    b->first.substr(0, s) == name &&
		    b->first[s] == '*')
			return true;
		b++;
	}
	return false;
}
