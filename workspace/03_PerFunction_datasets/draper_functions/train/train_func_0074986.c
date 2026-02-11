vmsg_send_head_ping(const struct sha1 *sha1, host_addr_t addr, uint16 port,
	const struct guid *guid)
{
	static const char urn_prefix[] = "urn:sha1:";
	struct gnutella_node *n;
	const struct guid *muid;
	uint32 msgsize;
	uint32 paysize;
	char *payload;
	uint8 flags = VMSG_HEAD_F_ALT;
	ggep_stream_t gs;
	size_t ggep_len;
	void *p;


	g_return_if_fail(sha1);
	n = node_udp_get_addr_port(addr, port);
	if (NULL == n)
		return;

	payload = vmsg_fill_type(v_tmp_data, T_LIME, 23, 2);

	p = mempcpy(&payload[1], urn_prefix, CONST_STRLEN(urn_prefix));
	p = mempcpy(p, sha1_base32(sha1), SHA1_BASE32_SIZE);
	paysize = ptr_diff(p, payload);


	ggep_stream_init(&gs, &payload[paysize],
		&v_tmp[sizeof(v_tmp)] - &payload[paysize]);


	if (guid != NULL) {
		(void) ggep_stream_pack(&gs, GGEP_NAME(PUSH), guid, GUID_RAW_SIZE, 0);
	}


	if (settings_running_ipv4()) {
		if (settings_running_ipv6()) {


			(void) ggep_stream_pack(&gs, GGEP_NAME(I6), NULL, 0, 0);
		}
	} else if (settings_running_ipv6()) {
		uint8 b = 1;


		(void) ggep_stream_pack(&gs, GGEP_NAME(I6), &b, sizeof b, 0);
	}

	ggep_len = ggep_stream_close(&gs);
	paysize += ggep_len;

	if (0 != ggep_len)
		flags |= VMSG_HEAD_F_GGEP;

	poke_u8(&payload[0], flags);

	msgsize = vmsg_fill_header(v_tmp_header, paysize, sizeof v_tmp);
	message_set_muid(v_tmp_header, GTA_MSG_VENDOR);
	muid = gnutella_header_get_muid(v_tmp_header);

	if (head_ping_register_own(muid, sha1, n)) {
		if (GNET_PROPERTY(vmsg_debug) > 1 || GNET_PROPERTY(log_vmsg_tx)) {
			g_debug(
				"VMSG sending HEAD Ping to %s (%u bytes) for urn:sha1:%s",
					node_infostr(n), paysize, sha1_base32(sha1));
		}
		vmsg_send_data(n, v_tmp, msgsize);
	}
}
