policy_check(unsigned int flags)
{
	struct xt_policy_info *info = policy_info;
	struct xt_policy_elem *e;
	int i;

	if (info == NULL)
		xtables_error(PARAMETER_PROBLEM,
		           "policy match: no parameters given");

	if (!(info->flags & (XT_POLICY_MATCH_IN | XT_POLICY_MATCH_OUT)))
		xtables_error(PARAMETER_PROBLEM,
		           "policy match: neither --dir in nor --dir out specified");

	if (info->flags & XT_POLICY_MATCH_NONE) {
		if (info->flags & XT_POLICY_MATCH_STRICT)
			xtables_error(PARAMETER_PROBLEM,
			           "policy match: policy none but --strict given");

		if (info->len != 0)
			xtables_error(PARAMETER_PROBLEM,
			           "policy match: policy none but policy given");
	} else
		info->len++;

	if (!(info->flags & XT_POLICY_MATCH_STRICT) && info->len > 1)
		xtables_error(PARAMETER_PROBLEM,
		           "policy match: multiple elements but no --strict");

	for (i = 0; i < info->len; i++) {
		e = &info->pol[i];

		if (info->flags & XT_POLICY_MATCH_STRICT &&
		    !(e->match.reqid || e->match.spi || e->match.saddr ||
		      e->match.daddr || e->match.proto || e->match.mode))
			xtables_error(PARAMETER_PROBLEM,
			           "policy match: empty policy element");

		if ((e->match.saddr || e->match.daddr)
		    && ((e->mode == XT_POLICY_MODE_TUNNEL && e->invert.mode) ||
		        (e->mode == XT_POLICY_MODE_TRANSPORT && !e->invert.mode)))
			xtables_error(PARAMETER_PROBLEM,
			           "policy match: --tunnel-src/--tunnel-dst "
			           "is only valid in tunnel mode");
	}
}
