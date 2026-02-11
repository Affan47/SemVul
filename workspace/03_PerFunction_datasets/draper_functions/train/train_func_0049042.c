vdi_dns_pick_host(const struct sess *sp, struct vdi_dns_hostgroup *group) {
	int initial, i, nhosts, current;
	if (group->nhosts == 0)
		return (NULL);
	if (group->next_host >= group->nhosts)
		group->next_host = 0;


	initial = group->next_host;
	nhosts = group->nhosts;
	for (i=0; i < nhosts; i++) {
		if (i + initial >= nhosts)
			current = i + initial - nhosts;
		else
			current = i + initial;
		if (VDI_Healthy(group->hosts[current], sp)) {
			group->next_host = current+1;
			return (group->hosts[current]);
		}
	}

	return (NULL);
}
