cgroup_print_opt(struct filter_util *qu, FILE *f,
			   struct rtattr *opt, __u32 handle)
{
	struct rtattr *tb[TCA_CGROUP_MAX+1];

	if (opt == NULL)
		return 0;

	parse_rtattr_nested(tb, TCA_CGROUP_MAX, opt);

	if (handle)
		fprintf(f, "handle 0x%x ", handle);

	if (tb[TCA_CGROUP_EMATCHES])
		print_ematch(f, tb[TCA_CGROUP_EMATCHES]);

	if (tb[TCA_CGROUP_POLICE]) {
		fprintf(f, "\n");
		tc_print_police(f, tb[TCA_CGROUP_POLICE]);
	}

	if (tb[TCA_CGROUP_ACT])
		tc_print_action(f, tb[TCA_CGROUP_ACT]);

	return 0;
}
