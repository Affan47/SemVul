hfsc_print_class_opt(struct qdisc_util *qu, FILE *f, struct rtattr *opt)
{
	struct rtattr *tb[TCA_HFSC_MAX+1];
	struct tc_service_curve *rsc = NULL, *fsc = NULL, *usc = NULL;

	if (opt == NULL)
		return 0;

	parse_rtattr_nested(tb, TCA_HFSC_MAX, opt);

	if (tb[TCA_HFSC_RSC]) {
		if (RTA_PAYLOAD(tb[TCA_HFSC_RSC]) < sizeof(*rsc))
			fprintf(stderr, "HFSC: truncated realtime option\n");
		else
			rsc = RTA_DATA(tb[TCA_HFSC_RSC]);
	}
	if (tb[TCA_HFSC_FSC]) {
		if (RTA_PAYLOAD(tb[TCA_HFSC_FSC]) < sizeof(*fsc))
			fprintf(stderr, "HFSC: truncated linkshare option\n");
		else
			fsc = RTA_DATA(tb[TCA_HFSC_FSC]);
	}
	if (tb[TCA_HFSC_USC]) {
		if (RTA_PAYLOAD(tb[TCA_HFSC_USC]) < sizeof(*usc))
			fprintf(stderr, "HFSC: truncated upperlimit option\n");
		else
			usc = RTA_DATA(tb[TCA_HFSC_USC]);
	}


	if (rsc != NULL && fsc != NULL &&
	    memcmp(rsc, fsc, sizeof(*rsc)) == 0)
		hfsc_print_sc(f, "sc", rsc);
	else {
		if (rsc != NULL)
			hfsc_print_sc(f, "rt", rsc);
		if (fsc != NULL)
			hfsc_print_sc(f, "ls", fsc);
	}
	if (usc != NULL)
		hfsc_print_sc(f, "ul", usc);

	return 0;
}
