generic_dns_callback(int result, char type, int count, int ttl, void *addresses,
    void *arg)
{
	size_t len;
	struct generic_dns_callback_result *res = arg;
	res->result = result;
	res->type = type;
	res->count = count;
	res->ttl = ttl;

	if (type == DNS_IPv4_A)
		len = count * 4;
	else if (type == DNS_IPv6_AAAA)
		len = count * 16;
	else if (type == DNS_PTR)
		len = strlen(addresses)+1;
	else {
		res->addrs_len = len = 0;
		res->addrs = NULL;
	}
	if (len) {
		res->addrs_len = len;
		if (len > 256)
			len = 256;
		memcpy(res->addrs_buf, addresses, len);
		res->addrs = res->addrs_buf;
	}

	--n_replies_left;
	if (n_replies_left == 0) {
		if (exit_port) {
			evdns_close_server_port(exit_port);
			exit_port = NULL;
		} else
			event_base_loopexit(exit_base, NULL);
	}
}
