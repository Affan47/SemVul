parse_choice_option(struct isl_arg *decl, char **arg,
	struct isl_prefixes *prefixes, void *opt)
{
	int i;
	int has_argument;
	const char *choice;

	choice = skip_name(decl, arg[0], prefixes, 0, &has_argument);
	if (!choice)
		return 0;

	if (!has_argument && (!arg[1] || arg[1][0] == '-')) {
		unsigned u = decl->u.choice.default_selected;
		*(unsigned *)(((char *)opt) + decl->offset) = u;
		if (decl->u.choice.set)
			decl->u.choice.set(opt, u);

		return 1;
	}

	if (!has_argument)
		choice = arg[1];

	for (i = 0; decl->u.choice.choice[i].name; ++i) {
		unsigned u;

		if (strcmp(choice, decl->u.choice.choice[i].name))
			continue;

		u = decl->u.choice.choice[i].value;
		*(unsigned *)(((char *)opt) + decl->offset) = u;
		if (decl->u.choice.set)
			decl->u.choice.set(opt, u);

		return has_argument ? 1 : 2;
	}

	return 0;
}
