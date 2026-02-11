print_mdb_entry(FILE *f, int ifindex, struct br_mdb_entry *e)
{
	SPRINT_BUF(abuf);

	if (e->addr.proto == htons(ETH_P_IP))
		fprintf(f, "dev %s port %s grp %s %s\n", ll_index_to_name(ifindex),
			ll_index_to_name(e->ifindex),
			inet_ntop(AF_INET, &e->addr.u.ip4, abuf, sizeof(abuf)),
			(e->state & MDB_PERMANENT) ? "permanent" : "temp");
	else
		fprintf(f, "dev %s port %s grp %s %s\n", ll_index_to_name(ifindex),
			ll_index_to_name(e->ifindex),
			inet_ntop(AF_INET6, &e->addr.u.ip6, abuf, sizeof(abuf)),
			(e->state & MDB_PERMANENT) ? "permanent" : "temp");
}
