shell_help_memory(int argc, const char *argv[])
{
	g_assert(argv);
	g_assert(argc > 0);

	if (argc > 1) {
#ifdef ALLOW_DUMP
		if (0 == ascii_strcasecmp(argv[1], "dump")) {
			return "memory dump ADDRESS LENGTH\n"
				"dumps LENGTH bytes of memory starting at ADDRESS\n";
		} else
#endif
		if (0 == ascii_strcasecmp(argv[1], "check")) {
			return "memory check [-sv] xmalloc\n"
				"run consistency checks on freelists\n"
				"-s : silent mode, only display summary at the end\n"
				"-v : verbosely report for each freelist\n";
		}
		else if (0 == ascii_strcasecmp(argv[1], "show")) {
			return
				"memory show options   # display memory options\n"
				"memory show pmap      # display VMM pmap\n"
				"memory show xmalloc   # display xmalloc() freelist info\n"
				"memory show zones     # display zone usage\n";
		} else if (0 == ascii_strcasecmp(argv[1], "stats")) {
			return "memory stats [-pu] halloc|omalloc|vmm|xmalloc|zalloc\n"
				"show statistics about specified memory sub-system\n"
				"-p : pretty-print numbers with thousands separators\n"
				"-u : show allocation usage statistics, if available\n";
		} else if (0 == ascii_strcasecmp(argv[1], "usage")) {
			return "memory usage zone <size> on|off|show\n"
				"show or turn on/off usage statistics for given zone\n";
		}
	} else {
		return
#ifdef ALLOW_DUMP
		"memory dump ADDRESS LENGTH\n"
#endif
		"memory check xmalloc\n"
		"memory show options|pmap|xmalloc|zones\n"
		"memory stats [-pu] omalloc|vmm|xmalloc|zalloc\n"
		"memory usage zone <size> on|off|show\n"
		;
	}
	return NULL;
}
