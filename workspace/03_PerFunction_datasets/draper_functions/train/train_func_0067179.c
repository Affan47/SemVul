conf_askvalue(struct symbol *sym, const char *def)
{
	enum symbol_type type = sym_get_type(sym);
	tristate val;

	if (!sym_has_value(sym))
		printf("(NEW) ");

	line[0] = '\n';
	line[1] = 0;

	if (!sym_is_changable(sym)) {
		printf("%s\n", def);
		line[0] = '\n';
		line[1] = 0;
		return;
	}

	switch (input_mode) {
	case ask_new:
	case ask_silent:
		if (sym_has_value(sym)) {
			printf("%s\n", def);
			return;
		}
		check_stdin();
	case ask_all:
		fflush(stdout);
		fgets(line, 128, stdin);
		return;
	case set_default:
		printf("%s\n", def);
		return;
	default:
		break;
	}

	switch (type) {
	case S_INT:
	case S_HEX:
	case S_STRING:
		printf("%s\n", def);
		return;
	default:
		;
	}
	switch (input_mode) {
	case set_yes:
		if (sym_tristate_within_range(sym, yes)) {
			line[0] = 'y';
			line[1] = '\n';
			line[2] = 0;
			break;
		}
	case set_mod:
		if (type == S_TRISTATE) {
			if (sym_tristate_within_range(sym, mod)) {
				line[0] = 'm';
				line[1] = '\n';
				line[2] = 0;
				break;
			}
		} else {
			if (sym_tristate_within_range(sym, yes)) {
				line[0] = 'y';
				line[1] = '\n';
				line[2] = 0;
				break;
			}
		}
	case set_no:
		if (sym_tristate_within_range(sym, no)) {
			line[0] = 'n';
			line[1] = '\n';
			line[2] = 0;
			break;
		}
	case set_random:
		do {
			val = (tristate)(random() % 3);
		} while (!sym_tristate_within_range(sym, val));
		switch (val) {
		case no: line[0] = 'n'; break;
		case mod: line[0] = 'm'; break;
		case yes: line[0] = 'y'; break;
		}
		line[1] = '\n';
		line[2] = 0;
		break;
	default:
		break;
	}
	printf("%s", line);
}
