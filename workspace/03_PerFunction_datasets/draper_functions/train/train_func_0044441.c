cmd_setbreak(char **arg)
{
	char *addr_text = get_arg(arg);
	char *index_text = get_arg(arg);
	int index = -1;
	address_t addr;

	if (!addr_text) {
		printc_err("setbreak: address required\n");
		return -1;
	}

	if (expr_eval(stab_default, addr_text, &addr) < 0) {
		printc_err("setbreak: invalid address\n");
		return -1;
	}

	if (index_text) {
		address_t val;

		if (expr_eval(stab_default, index_text, &val) < 0 ||
		    val >= device_default->max_breakpoints) {
			printc("setbreak: invalid breakpoint slot: %d\n", val);
			return -1;
		}

		index = val;
	}

	index = device_setbrk(device_default, index, 1, addr);
	if (index < 0) {
		printc_err("setbreak: all breakpoint slots are "
			"occupied\n");
		return -1;
	}

	printc("Set breakpoint %d\n", index);
	return 0;
}
