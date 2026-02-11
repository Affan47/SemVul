lookup_long_option(const std::string& long_option)
{
	for(Options::iterator i = options.begin(); i != options.end(); ++i)
	{
		if (i->long_option == long_option)
			return &*i;
	}
	return 0;
}
