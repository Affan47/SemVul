gnet_stats_count_received_payload(const gnutella_node_t *n, const void *payload)
{
	uint8 f = gnutella_header_get_function(&n->header);
	uint t = stats_lut[f];
	uint i;
	gnet_stats_t *stats;
    uint32 size;

	stats = NODE_USES_UDP(n) ? &gnet_udp_stats : &gnet_tcp_stats;


	size = n->size;
	gnet_stats_randomness(n, f, size);


	if (GTA_MSG_DHT == f && size + GTA_HEADER_SIZE >= KDA_HEADER_SIZE) {
		uint8 opcode = peek_u8(payload);

		if (UNSIGNED(opcode + MSG_DHT_BASE) < G_N_ELEMENTS(stats_lut)) {
			t = stats_lut[opcode + MSG_DHT_BASE];
			gnet_stats_count_kademlia_header(n, t);
		}
	}

    gnet_stats.byte.received[MSG_TOTAL] += size;
    gnet_stats.byte.received[t] += size;

    stats->byte.received[MSG_TOTAL] += size;
    stats->byte.received[t] += size;

	i = MIN(gnutella_header_get_ttl(&n->header), STATS_RECV_COLUMNS - 1);
    stats->byte.received_ttl[i][MSG_TOTAL] += size;
    stats->byte.received_ttl[i][t] += size;

	i = MIN(gnutella_header_get_hops(&n->header), STATS_RECV_COLUMNS - 1);
    stats->byte.received_hops[i][MSG_TOTAL] += size;
    stats->byte.received_hops[i][t] += size;
}
