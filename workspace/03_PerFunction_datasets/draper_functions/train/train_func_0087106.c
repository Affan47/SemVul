ipvs_mt_check(struct xt_fcheck_call *cb)
{
	struct xt_ipvs_mtinfo *info = cb->data;

	if (cb->xflags == 0)
		xtables_error(PARAMETER_PROBLEM,
			      "IPVS: At least one option is required");
	if (info->bitmask & XT_IPVS_ONCE_MASK) {
		if (info->invert & XT_IPVS_IPVS_PROPERTY)
			xtables_error(PARAMETER_PROBLEM,
				      "! --ipvs cannot be together with"
				      " other options");
		info->bitmask |= XT_IPVS_IPVS_PROPERTY;
	}
}
