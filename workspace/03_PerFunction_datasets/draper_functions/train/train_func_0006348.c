twoletter(CONST char *str)
{
	char		opt[3];

	if (str == 0) return;
	if (init()) return;


	opt[0] = *str++; opt[2] = '\0';

	if (*str == ':') ++str;

	for ( ; *str; ++str) {
		opt[1] = *str;
		if (ao_setopt(lam_args_optd, opt, (char *) 0, 0, AODOARGS))
		  return;
	}
}
