gnet_stats_count_kademlia_header(const gnutella_node_t *n, uint kt)
{
	uint t = stats_lut[gnutella_header_get_function(&n->header)];
	uint i;
	gnet_stats_t *stats;

	stats = NODE_USES_UDP(n) ? &gnet_udp_stats : &gnet_tcp_stats;

    gnet_stats.pkg.received[t]--;
    gnet_stats.pkg.received[kt]++;
    gnet_stats.byte.received[t] -= GTA_HEADER_SIZE;
    gnet_stats.byte.received[kt] += GTA_HEADER_SIZE;

    stats->pkg.received[t]--;
    stats->pkg.received[kt]++;
    stats->byte.received[t] -= GTA_HEADER_SIZE;
    stats->byte.received[kt] += GTA_HEADER_SIZE;

	i = MIN(gnutella_header_get_ttl(&n->header), STATS_RECV_COLUMNS - 1);
    stats->pkg.received_ttl[i][MSG_TOTAL]--;
    stats->pkg.received_ttl[i][t]--;

	i = MIN(gnutella_header_get_hops(&n->header), STATS_RECV_COLUMNS - 1);
    stats->pkg.received_hops[i][MSG_TOTAL]--;
    stats->pkg.received_hops[i][t]--;


    stats->pkg.received_ttl[0][MSG_TOTAL]++;
    stats->pkg.received_ttl[0][kt]++;
    stats->pkg.received_hops[0][MSG_TOTAL]++;
    stats->pkg.received_hops[0][kt]++;
}
