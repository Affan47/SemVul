print_gact(struct action_util *au,FILE * f, struct rtattr *arg)
{
	SPRINT_BUF(b1);
#ifdef CONFIG_GACT_PROB
	SPRINT_BUF(b2);
	struct tc_gact_p *pp = NULL;
	struct tc_gact_p pp_dummy;
#endif
	struct tc_gact *p = NULL;
	struct rtattr *tb[TCA_GACT_MAX + 1];

	if (arg == NULL)
		return -1;

	parse_rtattr_nested(tb, TCA_GACT_MAX, arg);

	if (tb[TCA_GACT_PARMS] == NULL) {
		fprintf(f, "[NULL gact parameters]");
		return -1;
	}
	p = RTA_DATA(tb[TCA_GACT_PARMS]);

	fprintf(f, "gact action %s", action_n2a(p->action, b1, sizeof (b1)));
#ifdef CONFIG_GACT_PROB
	if (NULL != tb[TCA_GACT_PROB]) {
		pp = RTA_DATA(tb[TCA_GACT_PROB]);
	} else {

		memset(&pp_dummy, 0, sizeof (pp_dummy));
		pp = &pp_dummy;
	}
	fprintf(f, "\n\t random type %s %s val %d",prob_n2a(pp->ptype), action_n2a(pp->paction, b2, sizeof (b2)), pp->pval);
#endif
	fprintf(f, "\n\t index %d ref %d bind %d",p->index, p->refcnt, p->bindcnt);
	if (show_stats) {
		if (tb[TCA_GACT_TM]) {
			struct tcf_t *tm = RTA_DATA(tb[TCA_GACT_TM]);
			print_tm(f,tm);
		}
	}
	fprintf(f, "\n ");
	return 0;
}
