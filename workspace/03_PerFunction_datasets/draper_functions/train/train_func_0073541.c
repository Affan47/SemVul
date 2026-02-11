k_send_store_response(
	struct gnutella_node *n,
	const knode_t *kn,
	dht_value_t **vec, uint8 vlen,
	bool valid_token,
	const guid_t *muid)
{
	pmsg_t *mb;
	kademlia_header_t *header;
	uint16 *status;
	int i;

	WALLOC_ARRAY(status, vlen);

	for (i = 0; i < vlen; i++)
		status[i] = values_store(kn, vec[i], valid_token);


	mb = pmsg_new(PMSG_P_CONTROL, NULL, MAX_STORE_RESPONSE_SIZE);

	header = (kademlia_header_t *) pmsg_start(mb);
	kmsg_build_header(header, KDA_MSG_STORE_RESPONSE, 0, 0, muid);

	pmsg_seek(mb, KDA_HEADER_SIZE);


	pmsg_write_u8(mb, vlen);

	for (i = 0; i < vlen; i++) {
		if (pmsg_available(mb) < 44)
			break;


		pmsg_write(mb, dht_value_key(vec[i])->v, KUID_RAW_SIZE);
		pmsg_write(mb, dht_value_creator(vec[i])->id->v, KUID_RAW_SIZE);
		pmsg_write_be16(mb, status[i]);
		pmsg_write_be16(mb, 0);
	}

	if (i < vlen) {
		pmsg_offset_t cur = pmsg_write_offset(mb);
		pmsg_seek(mb, KDA_HEADER_SIZE);
		pmsg_write_u8(mb, i);
		pmsg_seek(mb, cur);

		if (GNET_PROPERTY(dht_debug))
			g_warning("DHT sending back only %d out of %u STORE statuses to %s",
				i, vlen, knode_to_string(kn));
	}

	kademlia_header_set_size(header, pmsg_size(mb) - KDA_HEADER_SIZE);


	if (GNET_PROPERTY(dht_debug > 3))
		g_debug("DHT sending back %s (%zu bytes) with %d status%s to %s",
			kmsg_infostr(header), (size_t) pmsg_size(mb),
			i, i == 1 ? "" : "es",
			host_addr_port_to_string(n->addr, n->port));

	udp_dht_send_mb(n, mb);


	WFREE_ARRAY(status, vlen);
}
