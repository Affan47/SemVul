del_ip_route(unsigned long ip)
{
	ip_rt_entry *bp;

	if (ip == 0)
		return 1;

	for (bp = ip_routes; bp; bp = bp->next)
		if (bp->ip == ip) {
			remove_ip_route(bp);
			return 0;
		}

	return 1;
}
