parse_encapsulated_suboptions (struct option_state *options,
				   struct option *eopt,
				   const unsigned char *buffer,
				   unsigned len, struct universe *eu,
				   const char *uname)
{
	int i;
	struct universe *universe = find_option_universe (eopt, uname);


	if (!universe)
		return 0;


	if (!universe -> decode)
		return 0;

	i = (*universe -> decode) (options, buffer, len, universe);


	if (eopt -> format [0] != 'E')
		return 0;

	return i;
}
