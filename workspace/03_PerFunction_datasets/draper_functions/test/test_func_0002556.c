lookup_short_option(char short_option)
{
	for(Options::iterator i = options.begin(); i != options.end(); ++i)
	{
		if (i->key == short_option)
			return &(*i);
	}
	return 0;
}
