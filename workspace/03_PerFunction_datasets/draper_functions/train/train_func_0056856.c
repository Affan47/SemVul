qdisc_fq_codel(struct qdisc_opt *qopt, struct nlmsghdr *n)
{
	struct rtattr *tail = NLMSG_TAIL(n);

	addattr_l(n, 1024, TCA_OPTIONS, NULL, 0);

	if (conf_lq_arg1)
		addattr_l(n, 1024, TCA_FQ_CODEL_LIMIT, &conf_lq_arg1, sizeof(conf_lq_arg1));
	if (conf_lq_arg2)
		addattr_l(n, 1024, TCA_FQ_CODEL_FLOWS, &conf_lq_arg2, sizeof(conf_lq_arg2));
	if (conf_lq_arg3)
		addattr_l(n, 1024, TCA_FQ_CODEL_QUANTUM, &conf_lq_arg3, sizeof(conf_lq_arg3));
	if (conf_lq_arg4)
		addattr_l(n, 1024, TCA_FQ_CODEL_INTERVAL, &conf_lq_arg4, sizeof(conf_lq_arg4));
	if (conf_lq_arg5)
		addattr_l(n, 1024, TCA_FQ_CODEL_TARGET, &conf_lq_arg5, sizeof(conf_lq_arg5));
	if (conf_lq_arg6 != -1)
		addattr_l(n, 1024, TCA_FQ_CODEL_ECN, &conf_lq_arg6, sizeof(conf_lq_arg6));

	tail->rta_len = (void *)NLMSG_TAIL(n) - (void *)tail;

	return 0;
}
