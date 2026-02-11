gdht_handle_nope(const lookup_val_rc_t *rc, struct guid_lookup *glk)
{
	extvec_t exv[MAX_EXTVEC];
	int exvcnt;
	int i;
	guid_t guid;
	uint16 port = 0;

	g_assert(DHT_VT_NOPE == rc->type);
	guid_lookup_check(glk);

	ext_prepare(exv, MAX_EXTVEC);
	ZERO(&guid.v);

	exvcnt = ext_parse(rc->data, rc->length, exv, MAX_EXTVEC);

	for (i = 0; i < exvcnt; i++) {
		extvec_t *e = &exv[i];
		uint16 paylen;

		switch (e->ext_token) {
		case EXT_T_GGEP_guid:
			if (GUID_RAW_SIZE == ext_paylen(e))
				memcpy(guid.v, ext_payload(e), GUID_RAW_SIZE);
			break;
		case EXT_T_GGEP_port:
			if (2 == ext_paylen(e))
				port = peek_be16(ext_payload(e));
			break;
		case EXT_T_GGEP_tls:

			break;
		default:
			if (GNET_PROPERTY(ggep_debug) > 1 && e->ext_type == EXT_GGEP) {
				paylen = ext_paylen(e);
				g_warning("%s: unhandled GGEP \"%s\" (%d byte%s)",
					value_infostr(rc),
					ext_ggep_id_str(e), paylen, paylen == 1 ? "" : "s");
			}
			break;
		}
	}


	if (!guid_eq(glk->guid, &guid)) {
		if (GNET_PROPERTY(download_debug))
			g_warning("discarding %s from %s for GUID %s: NOPE was for GUID %s",
				value_infostr(rc), host_addr_port_to_string(rc->addr, port),
				guid_to_string(glk->guid), guid_hex_str(&guid));
		goto cleanup;
	}


	if (port) {
		if (port != rc->port && GNET_PROPERTY(download_debug))
			g_warning("%s: port mismatch: creator's was %u, "
				"NOPE is %u for %s, known as %s here",
				value_infostr(rc), rc->port,
				port, host_addr_to_string(rc->addr),
				host_addr_port_to_string(glk->addr, glk->port));
	} else {
		port = rc->port;
	}


	if (GNET_PROPERTY(download_debug) > 0)
		g_debug("adding %s [%s] (NOPE creator) as push-proxy for %s (%s)",
			host_addr_port_to_string(rc->addr, port),
			vendor_to_string(rc->vcode), guid_to_string(glk->guid),
			host_addr_port_to_string2(glk->addr, glk->port));

	download_add_push_proxy(glk->guid, rc->addr, port);


cleanup:
	if (exvcnt)
		ext_reset(exv, MAX_EXTVEC);
}
