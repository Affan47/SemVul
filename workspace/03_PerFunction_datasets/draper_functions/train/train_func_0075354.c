build_guess_ping_msg(const struct guid *muid, bool qk, bool intro, bool scp,
	uint32 *size)
{
	static union {
		gnutella_msg_init_t s;
		char buf[256];
		uint64 align8;
	} msg_init;
	gnutella_msg_init_t *m = &msg_init.s;
	uint32 sz;
	uchar *ggep;
	ggep_stream_t gs;
	bool ok;

	g_assert(qk || intro);

	STATIC_ASSERT(sizeof *m <= sizeof msg_init.buf);
	STATIC_ASSERT(GTA_HEADER_SIZE == sizeof *m);

	if (muid)
		gnutella_header_set_muid(m, muid);
	else
		message_set_muid(m, GTA_MSG_INIT);

	gnutella_header_set_function(m, GTA_MSG_INIT);
	gnutella_header_set_ttl(m, 1);
	gnutella_header_set_hops(m, 0);

	sz = 0;
	ggep = cast_to_pointer(&m[1]);
	ggep_stream_init(&gs, ggep, sizeof msg_init.buf - sizeof *m);

	if (scp) {
		if (qk) {
			char spp;


			spp = settings_is_leaf() ? 0 : SCP_F_ULTRA;
			spp |= tls_enabled() ? SCP_F_TLS : 0;


			spp |= settings_running_ipv6() ? SCP_F_IPV6 : 0;
			spp |= settings_running_ipv6_only() ? SCP_F_NO_IPV4 : 0;

			ok = ggep_stream_pack(&gs, GGEP_NAME(SCP), &spp, sizeof spp, 0);
			g_assert(ok);
		} else if (!intro || !settings_is_ultra()) {


			ggep_stream_pack(&gs, GGEP_NAME(GUE), NULL, 0, 0);
		}
	}

	if (qk) {
		ggep_stream_pack(&gs, GGEP_NAME(QK), NULL, 0, 0);
	}


	if (intro && settings_is_ultra()) {
		char buf[3];
		poke_u8(&buf[0], (SEARCH_GUESS_MAJOR << 4) | SEARCH_GUESS_MINOR);
		poke_le16(&buf[1], socket_listen_port());
		ggep_stream_pack(&gs, GGEP_NAME(GUE), buf, sizeof buf, 0);
	}

	sz += ggep_stream_close(&gs);

	gnutella_header_set_size(m, sz);

	if (size)
		*size = sz + GTA_HEADER_SIZE;

	return m;
}
