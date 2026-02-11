limit_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_rateinfo *r = (const void *)match->data;

	printf(" --limit"); print_rate(r->avg);
	if (r->burst != XT_LIMIT_BURST)
		printf(" --limit-burst %u", r->burst);
}
