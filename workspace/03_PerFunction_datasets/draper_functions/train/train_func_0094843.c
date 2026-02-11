bond_opt_get_by_name(const char *name)
{
	const struct bond_option *opt;
	int option;

	for (option = 0; option < BOND_OPT_LAST; option++) {
		opt = bond_opt_get(option);
		if (opt && !strcmp(opt->name, name))
			return opt;
	}

	return NULL;
}
