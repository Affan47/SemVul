eel_spec_function(void)
{
	int c;

	if(_proc_func() < 0)
		return -1;


	while((c = bio_getchar(eel_current.bio)) != '}')
		if(EOF == c)
		{
			eel_error("EOF inside function body!");
			return -1;
		}

	return 1;
}
