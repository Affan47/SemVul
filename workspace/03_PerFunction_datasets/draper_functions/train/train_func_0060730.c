jas_optlookup(jas_opt_t *opts, char *name)
{
	jas_opt_t *opt;

	for (opt = opts; opt->id >= 0 && opt->name; ++opt) {
		if (!strcmp(opt->name, name)) {
			return opt;
		}
	}
	return 0;
}
