print_match(const struct xt_statistic_info *info, char *prefix)
{
	switch (info->mode) {
	case XT_STATISTIC_MODE_RANDOM:
		printf(" %smode random%s %sprobability %.11f", prefix,
		       (info->flags & XT_STATISTIC_INVERT) ? " !" : "",
		       prefix,
		       1.0 * info->u.random.probability / 0x80000000);
		break;
	case XT_STATISTIC_MODE_NTH:
		printf(" %smode nth%s %severy %u", prefix,
		       (info->flags & XT_STATISTIC_INVERT) ? " !" : "",
		       prefix,
		       info->u.nth.every + 1);
		if (info->u.nth.packet || *prefix)
			printf(" %spacket %u", prefix, info->u.nth.packet);
		break;
	}
}
