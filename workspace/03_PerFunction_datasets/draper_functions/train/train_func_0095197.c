tridentfb_setup(char *options)
{
	char *opt;
	if (!options || !*options)
		return 0;
	while ((opt = strsep(&options, ",")) != NULL) {
		if (!*opt)
			continue;
		if (!strncmp(opt, "noaccel", 7))
			noaccel = 1;
		else if (!strncmp(opt, "fp", 2))
			fp = 1;
		else if (!strncmp(opt, "crt", 3))
			fp = 0;
		else if (!strncmp(opt, "bpp=", 4))
			bpp = simple_strtoul(opt + 4, NULL, 0);
		else if (!strncmp(opt, "center", 6))
			center = 1;
		else if (!strncmp(opt, "stretch", 7))
			stretch = 1;
		else if (!strncmp(opt, "memsize=", 8))
			memsize = simple_strtoul(opt + 8, NULL, 0);
		else if (!strncmp(opt, "memdiff=", 8))
			memdiff = simple_strtoul(opt + 8, NULL, 0);
		else if (!strncmp(opt, "nativex=", 8))
			nativex = simple_strtoul(opt + 8, NULL, 0);
		else
			mode_option = opt;
	}
	return 0;
}
