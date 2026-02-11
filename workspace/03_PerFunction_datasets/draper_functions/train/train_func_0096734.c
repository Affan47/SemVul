iscsi_target_show_portals(struct iscsi_target *target, uint64_t sid,
				   char *buf, int rest)
{
	int len = 0, total = 0;
	struct iscsi_portal *portal;

	list_for_each_entry(portal, &iscsi_portals_list,
			iscsi_portal_siblings) {
		int is_ipv6;

		is_ipv6 = strchr(portal->addr, ':') != NULL;
		len = snprintf(buf, rest,
			       "Portal: %s%s%s:%d,%d\n",
			       is_ipv6 ? "[" : "",
			       portal->addr,
			       is_ipv6 ? "]" : "",
			       portal->port ? portal->port : ISCSI_LISTEN_PORT,
			       portal->tpgt);
		__buffer_check(buf, total, len, rest);
	}

	return total;

}
