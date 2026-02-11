_icq_makesnac(uint8_t family, uint16_t cmd, uint16_t flags, uint32_t ref) {
	static char buf[SNAC_PACKET_LEN];
	string_t tempstr;

	tempstr = icq_pack("WWWI", (uint32_t) family, (uint32_t) cmd, (uint32_t) flags, (uint32_t) ref);
	if (tempstr->len != SNAC_PACKET_LEN) {
		debug_error("_icq_makesnac() critical error\n");
		return NULL;
	}
	memcpy(buf, tempstr->str, SNAC_PACKET_LEN);
	string_free(tempstr, 1);
	return buf;
}
