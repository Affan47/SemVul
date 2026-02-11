cproxy_create(struct download *d, const host_addr_t addr, uint16 port,
	const struct guid *guid, uint32 file_idx)
{
	struct cproxy *cp;
	struct array packet;

	WALLOC0(cp);
	cp->magic = CPROXY_MAGIC;
	cp->d = d;
	cp->addr = addr;
	cp->port = port;
	cp->guid = atom_guid_get(guid);
	cp->file_idx = file_idx == URN_INDEX ? 0 : file_idx;
	cp->flags = 0;


	packet = build_push(GNET_PROPERTY(max_ttl), 0 ,
		cp->guid, listen_addr(), listen_addr6(), cp->port,
		cp->file_idx, tls_enabled());

	if (packet.data) {
		if (download_send_udp_push(packet, cp->addr, cp->port)) {
			cp->udp_ev = cq_main_insert(CPROXY_UDP_MS, cproxy_http_start, cp);
		} else {
			cproxy_async_http_request(cp);
		}
	} else {
		cproxy_async_http_request(cp);
	}

	return cp;
}
