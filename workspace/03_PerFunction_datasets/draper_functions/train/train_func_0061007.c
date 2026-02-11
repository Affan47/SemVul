pppoe_serv_read(struct triton_md_handler_t *h)
{
	struct pppoe_serv_t *serv = container_of(h, typeof(*serv), hnd);
	uint8_t pack[ETHER_MAX_LEN];
	struct ethhdr *ethhdr = (struct ethhdr *)pack;
	struct pppoe_hdr *hdr = (struct pppoe_hdr *)(pack + ETH_HLEN);
	int n;

	while (1) {
		n = read(h->fd, pack, sizeof(pack));
		if (n < 0) {
			if (errno == EAGAIN)
				break;
			if (errno == ENETDOWN) {
				_server_stop(serv);
				return 1;
			}
			log_error("pppoe: read: %s\n", strerror(errno));
			return 0;
		}

		if (n < ETH_HLEN + sizeof(*hdr)) {
			if (conf_verbose)
				log_warn("pppoe: short packet received (%i)\n", n);
			continue;
		}

		if (mac_filter_check(ethhdr->h_source)) {
			__sync_add_and_fetch(&stat_filtered, 1);
			continue;
		}

		if (memcmp(ethhdr->h_dest, bc_addr, ETH_ALEN) && memcmp(ethhdr->h_dest, serv->hwaddr, ETH_ALEN))
			continue;

		if (!memcmp(ethhdr->h_source, bc_addr, ETH_ALEN)) {
			if (conf_verbose)
				log_warn("pppoe: discarding packet (host address is broadcast)\n");
			continue;
		}

		if ((ethhdr->h_source[0] & 1) != 0) {
			if (conf_verbose)
				log_warn("pppoe: discarding packet (host address is not unicast)\n");
			continue;
		}

		if (n < ETH_HLEN + sizeof(*hdr) + ntohs(hdr->length)) {
			if (conf_verbose)
				log_warn("pppoe: short packet received\n");
			continue;
		}

		if (hdr->ver != 1) {
			if (conf_verbose)
				log_warn("pppoe: discarding packet (unsupported version %i)\n", hdr->ver);
			continue;
		}

		if (hdr->type != 1) {
			if (conf_verbose)
				log_warn("pppoe: discarding packet (unsupported type %i)\n", hdr->type);
		}

		switch (hdr->code) {
			case CODE_PADI:
				pppoe_recv_PADI(serv, pack, n);
				break;
			case CODE_PADR:
				pppoe_recv_PADR(serv, pack, n);
				break;
			case CODE_PADT:
				pppoe_recv_PADT(serv, pack);
				break;
		}
	}
	return 0;
}
