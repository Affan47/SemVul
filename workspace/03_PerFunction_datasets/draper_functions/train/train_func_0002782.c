main(int ac, char **av)
{
	struct symbol *sym;
	char *mode;
	int stat;

	conf_parse(av[1]);
	conf_read(NULL);

	sym = sym_lookup("KERNELRELEASE", 0);
	sym_calc_value(sym);
	sprintf(menu_backtitle, "Linux Kernel v%s Configuration",
		sym_get_string_value(sym));

	mode = getenv("MENUCONFIG_MODE");
	if (mode) {
		if (!strcasecmp(mode, "single_menu"))
			single_menu_mode = 1;
	}

	tcgetattr(1, &ios_org);
	atexit(conf_cleanup);
	init_wsize();
	conf(&rootmenu);

	do {
		cprint_init();
		cprint("--yesno");
		cprint("Do you wish to save your new kernel configuration?");
		cprint("5");
		cprint("60");
		stat = exec_conf();
	} while (stat < 0);

	if (stat == 0) {
		if (conf_write(NULL)) {
			fprintf(stderr, "\n\n"
				"Error during writing of the kernel configuration.\n"
				"Your kernel configuration changes were NOT saved."
				"\n\n");
			return 1;
		}
		printf("\n\n"
			"*** End of Linux kernel configuration.\n"
			"*** Execute 'make' to build the kernel or try 'make help'."
			"\n\n");
	} else {
		fprintf(stderr, "\n\n"
			"Your kernel configuration changes were NOT saved."
			"\n\n");
	}

	return 0;
}
