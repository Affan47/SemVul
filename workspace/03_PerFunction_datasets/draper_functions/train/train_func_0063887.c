get_ipv4(struct ap_session *ses)
{
	struct radius_pd_t *rpd = find_pd(ses);

	if (rpd->ipv4_addr.peer_addr)
		return &rpd->ipv4_addr;
	return NULL;
}
