get_ipv6_prefix(struct ap_session *ses)
{
	struct radius_pd_t *rpd = find_pd(ses);

	if (!list_empty(&rpd->ipv6_dp.prefix_list)) {
		rpd->ipv6_dp_assigned = 1;
		return &rpd->ipv6_dp;
	}

	return NULL;
}
