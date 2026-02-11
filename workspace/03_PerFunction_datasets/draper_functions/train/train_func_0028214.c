ps_main(int argc UNUSED_PARAM, char **argv)
{
	procps_status_t *p;
	llist_t* opt_o = NULL;
	int opt;
	enum {
		OPT_Z = (1 << 0),
		OPT_o = (1 << 1),
		OPT_a = (1 << 2),
		OPT_A = (1 << 3),
		OPT_d = (1 << 4),
		OPT_e = (1 << 5),
		OPT_f = (1 << 6),
		OPT_l = (1 << 7),
		OPT_T = (1 << 8) * ENABLE_FEATURE_SHOW_THREADS,
	};

	INIT_G();


	opt_complementary = "o::";
	opt = getopt32(argv, "Zo:aAdefl"IF_FEATURE_SHOW_THREADS("T"), &opt_o);
	if (opt_o) {
		do {
			parse_o(llist_pop(&opt_o));
		} while (opt_o);
	} else {

#if ENABLE_SELINUX
		if (!(opt & OPT_Z) || !is_selinux_enabled()) {

			strcpy(default_o, DEFAULT_O_STR + sizeof(SELINUX_O_PREFIX)-1);
		} else
#endif
		{
			strcpy(default_o, DEFAULT_O_STR);
		}
		parse_o(default_o);
	}
#if ENABLE_FEATURE_SHOW_THREADS
	if (opt & OPT_T)
		need_flags |= PSSCAN_TASKS;
#endif


	terminal_width = MAX_WIDTH;
	if (isatty(1)) {
		get_terminal_width_height(0, &terminal_width, NULL);
		if (--terminal_width > MAX_WIDTH)
			terminal_width = MAX_WIDTH;
	}
	alloc_line_buffer();
	format_header();

	p = NULL;
	while ((p = procps_scan(p, need_flags)) != NULL) {
		format_process(p);
	}

	return EXIT_SUCCESS;
}
