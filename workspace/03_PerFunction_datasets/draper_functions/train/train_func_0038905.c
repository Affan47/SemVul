RATEEST_parse(int c, char **argv, int invert, unsigned int *flags,
	      const void *entry, struct xt_entry_target **target)
{
	struct xt_rateest_target_info *info = (void *)(*target)->data;

	RATEEST_info = info;

	switch (c) {
	case RATEEST_OPT_NAME:
		if (*flags & (1 << c))
			xtables_error(PARAMETER_PROBLEM,
				   "RATEEST: can't specify --rateest-name twice");
		*flags |= 1 << c;

		strncpy(info->name, optarg, sizeof(info->name) - 1);
		break;

	case RATEEST_OPT_INTERVAL:
		if (*flags & (1 << c))
			xtables_error(PARAMETER_PROBLEM,
				   "RATEEST: can't specify --rateest-interval twice");
		*flags |= 1 << c;

		if (RATEEST_get_time(&interval, optarg) < 0)
			xtables_error(PARAMETER_PROBLEM,
				   "RATEEST: bad interval value `%s'", optarg);

		break;

	case RATEEST_OPT_EWMALOG:
		if (*flags & (1 << c))
			xtables_error(PARAMETER_PROBLEM,
				   "RATEEST: can't specify --rateest-ewmalog twice");
		*flags |= 1 << c;

		if (RATEEST_get_time(&ewma_log, optarg) < 0)
			xtables_error(PARAMETER_PROBLEM,
				   "RATEEST: bad ewmalog value `%s'", optarg);

		break;
	}

	return 1;
}
