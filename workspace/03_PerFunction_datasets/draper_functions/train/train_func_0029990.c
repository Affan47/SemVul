knot_tsig_create_sign_wire(const uint8_t *msg, size_t msg_len,
				      const uint8_t *request_mac,
		                      size_t request_mac_len,
		                      uint8_t *digest, size_t *digest_len,
				      const knot_rrset_t *tmp_tsig,
		                      const knot_tsig_key_t *key)
{
	if (!msg || !key || digest_len == NULL) {
		dbg_tsig("TSIG: create wire: bad args.\n");
		return KNOT_EINVAL;
	}


	int ret = KNOT_EOK;


	dbg_tsig_verb("Counting wire size: %zu, %zu, %zu.\n",
	              msg_len, request_mac_len,
	              tsig_rdata_tsig_variables_length(tmp_tsig));
	size_t wire_len = sizeof(uint8_t) *
			(msg_len + request_mac_len + ((request_mac_len > 0)
			 ? 2 : 0) +
			tsig_rdata_tsig_variables_length(tmp_tsig));
	uint8_t *wire = malloc(wire_len);
	if (!wire) {
		ERR_ALLOC_FAILED;
		return KNOT_ENOMEM;
	}

	memset(wire, 0, wire_len);

	uint8_t *pos = wire;


	if (request_mac_len > 0) {
		dbg_tsig_verb("Copying request MAC size\n");
		knot_wire_write_u16(pos, request_mac_len);
		pos += 2;
		dbg_tsig_verb("Copying request mac.\n");
		memcpy(pos, request_mac, sizeof(uint8_t) * request_mac_len);
	}
	dbg_tsig_detail("TSIG: create wire: request mac:\n");
	dbg_tsig_hex_detail((char *)pos, request_mac_len);
	pos += request_mac_len;

	dbg_tsig_verb("Copying original message.\n");
	memcpy(pos, msg, msg_len);
	pos += msg_len;

	dbg_tsig_verb("Writing TSIG variables.\n");
	ret = knot_tsig_write_tsig_variables(pos, tmp_tsig);
	if (ret != KNOT_EOK) {
		dbg_tsig("TSIG: create wire: failed to write TSIG "
		         "variables: %s\n", knot_strerror(ret));
		free(wire);
		return ret;
	}


	ret = knot_tsig_compute_digest(wire, wire_len, digest, digest_len, key);
	if (ret != KNOT_EOK) {
		dbg_tsig("TSIG: create wire: failed to compute digest: %s\n",
		         knot_strerror(ret));
		*digest_len = 0;
		free(wire);
		return ret;
	}

	free(wire);

	return KNOT_EOK;
}
