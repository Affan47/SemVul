ia_pd_match_release(const struct data_string *client_id,
		    const struct data_string *iapref,
		    struct iasubopt *prefix)
{
	char tmp_addr[INET6_ADDRSTRLEN];

	log_info("Client %s releases prefix %s/%u",
		 print_hex_1(client_id->len, client_id->data, 60),
		 inet_ntop(AF_INET6, iapref->data + 9,
			   tmp_addr, sizeof(tmp_addr)),
		 (unsigned) getUChar(iapref->data + 8));
	if (prefix != NULL) {
		release_lease6(prefix->ipv6_pool, prefix);
		prefix->ia->cltt = cur_time;
		write_ia(prefix->ia);
	}
}
