gnet_host_vec_from_sequence(sequence_t *s)
{
	sequence_iter_t *iter;
	gnet_host_vec_t *vec;
	uint n_ipv6 = 0, n_ipv4 = 0, hcnt;

	if (sequence_is_empty(s))
		return NULL;

	hcnt = 0;
	iter = sequence_forward_iterator(s);
	while (sequence_iter_has_next(iter)) {
		const gnet_host_t *host = sequence_iter_next(iter);

		switch (gnet_host_get_net(host)) {
		case NET_TYPE_IPV4:
			n_ipv4++;
			hcnt++;
			break;
		case NET_TYPE_IPV6:
			n_ipv6++;
			hcnt++;
			break;
		case NET_TYPE_LOCAL:
		case NET_TYPE_NONE:
			break;
		}
	}
	sequence_iterator_release(&iter);
	if (0 == hcnt)
		return NULL;

	vec = gnet_host_vec_alloc();
	vec->n_ipv4 = MIN(n_ipv4, 255);
	vec->n_ipv6 = MIN(n_ipv6, 255);

	if (vec->n_ipv4 > 0)
		WALLOC_ARRAY(vec->hvec_v4, vec->n_ipv4);
	if (vec->n_ipv6 > 0)
		WALLOC_ARRAY(vec->hvec_v6, vec->n_ipv6);

	n_ipv4 = 0;
	n_ipv6 = 0;

	iter = sequence_forward_iterator(s);
	while (sequence_iter_has_next(iter)) {
		const gnet_host_t *host = sequence_iter_next(iter);
		host_addr_t addr = gnet_host_get_addr(host);
		uint16 port = gnet_host_get_port(host);

		switch (gnet_host_get_net(host)) {
		case NET_TYPE_IPV4:
			if (n_ipv4 < vec->n_ipv4) {
				char *dest = cast_to_pointer(&vec->hvec_v4[n_ipv4++]);
				poke_be32(&dest[0], host_addr_ipv4(addr));
				poke_le16(&dest[4], port);
			}
			break;
		case NET_TYPE_IPV6:
			if (n_ipv6 < vec->n_ipv6) {
				char *dest = cast_to_pointer(&vec->hvec_v6[n_ipv6++]);
				dest = mempcpy(dest, host_addr_ipv6(&addr), 16);
				poke_le16(dest, port);
			}
			break;
		case NET_TYPE_LOCAL:
		case NET_TYPE_NONE:
			break;
		}
	}
	sequence_iterator_release(&iter);
	return vec;
}
