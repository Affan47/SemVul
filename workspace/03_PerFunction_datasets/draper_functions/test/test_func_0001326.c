xtopt_parse_plen(struct xt_option_call *cb)
{
	const struct xt_option_entry *entry = cb->entry;
	unsigned int prefix_len = 128;

	cb->val.hlen = (afinfo->family == NFPROTO_IPV4) ? 32 : 128;
	if (!xtables_strtoui(cb->arg, NULL, &prefix_len, 0, cb->val.hlen))
		xt_params->exit_err(PARAMETER_PROBLEM,
			"%s: bad value for option \"--%s\", "
			"or out of range (%u-%u).\n",
			cb->ext_name, entry->name, 0, cb->val.hlen);

	cb->val.hlen = prefix_len;
}
