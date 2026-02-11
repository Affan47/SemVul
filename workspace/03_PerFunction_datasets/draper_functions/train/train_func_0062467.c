fw_print_opt(struct filter_util *qu, FILE *f, struct rtattr *opt, __u32 handle)
{
	struct rtattr *tb[TCA_FW_MAX+1];

	if (opt == NULL)
		return 0;

	parse_rtattr_nested(tb, TCA_FW_MAX, opt);

	if (handle || tb[TCA_FW_MASK]) {
		__u32 mark = 0, mask = 0;
		if(handle)
			mark = handle;
		if(tb[TCA_FW_MASK] &&
		    (mask = rta_getattr_u32(tb[TCA_FW_MASK])) != 0xFFFFFFFF)
			fprintf(f, "handle 0x%x/0x%x ", mark, mask);
		else
			fprintf(f, "handle 0x%x ", handle);
	}

	if (tb[TCA_FW_CLASSID]) {
		SPRINT_BUF(b1);
		fprintf(f, "classid %s ", sprint_tc_classid(rta_getattr_u32(tb[TCA_FW_CLASSID]), b1));
	}

	if (tb[TCA_FW_POLICE])
		tc_print_police(f, tb[TCA_FW_POLICE]);
	if (tb[TCA_FW_INDEV]) {
		struct rtattr *idev = tb[TCA_FW_INDEV];
		fprintf(f, "input dev %s ",rta_getattr_str(idev));
	}

	if (tb[TCA_FW_ACT]) {
		fprintf(f, "\n");
		tc_print_action(f, tb[TCA_FW_ACT]);
	}
	return 0;
}
