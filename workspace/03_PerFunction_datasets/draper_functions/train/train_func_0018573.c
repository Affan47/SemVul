vfb_setup(char *options)
{
	char *this_opt;

	vfb_enable = 0;

	if (!options)
		return 1;

	vfb_enable = 1;

	if (!*options)
		return 1;

	while ((this_opt = strsep(&options, ",")) != NULL) {
		if (!*this_opt)
			continue;

		if (!strcmp(this_opt, "disable"))
			vfb_enable = 0;
	}
	return 1;
}
