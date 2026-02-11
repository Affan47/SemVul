xtopt_parse_int(struct xt_option_call *cb)
{
	const struct xt_option_entry *entry = cb->entry;
	unsigned int lmin = 0, lmax = UINT32_MAX;
	unsigned int value;

	if (entry->type == XTTYPE_UINT8)
		lmax = UINT8_MAX;
	if (cb->entry->min != 0)
		lmin = cb->entry->min;
	if (cb->entry->max != 0)
		lmax = cb->entry->max;

	if (!xtables_strtoui(cb->arg, NULL, &value, lmin, lmax))
		xt_params->exit_err(PARAMETER_PROBLEM,
			"%s: bad value for option \"--%s\", "
			"or out of range (%u-%u).\n",
			cb->ext_name, entry->name, lmin, lmax);

	if (entry->type == XTTYPE_UINT8) {
		cb->val.u8 = value;
		if (entry->flags & XTOPT_PUT)
			*(uint8_t *)XTOPT_MKPTR(cb) = cb->val.u8;
	} else if (entry->type == XTTYPE_UINT32) {
		cb->val.u32 = value;
		if (entry->flags & XTOPT_PUT)
			*(uint32_t *)XTOPT_MKPTR(cb) = cb->val.u32;
	}
}
