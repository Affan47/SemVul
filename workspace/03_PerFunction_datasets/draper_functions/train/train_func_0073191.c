print_options(struct list_head *opt_list, int level, void (*print)(const char *fmt, ...))
{
	struct dhcpv6_option *opt;
	struct dict_option *dopt;
	const char l_open[] = {'<', '{', '('};
	const char l_close[] = {'>', '}', ')'};

	if (level >= sizeof(l_open))
		level = sizeof(l_open) - 1;

	list_for_each_entry(opt, opt_list, entry) {
		for (dopt = known_options; dopt->code; dopt++) {
			if (htons(dopt->code) == opt->hdr->code)
				break;
		}
		if (dopt->code) {
			print(" %c%s", l_open[level], dopt->name);
			if (dopt->print)
				dopt->print(opt, print);

			print_options(&opt->opt_list, level + 1, print);

			print("%c", l_close[level]);
		} else
			print(" %cOption %i%c", l_open[level], ntohs(opt->hdr->code), l_close[level]);
	}
}
