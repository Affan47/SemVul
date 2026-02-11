setTag(set<string> &keywords)
{
	set<string>::iterator b=keywords.begin(), e=keywords.end();

	tag=0;

	while (b != e)
	{
		size_t n;

		if (Tags::tags.isTagName(*b, n) && n > tag)
			tag=n;
		++b;
	}
}
