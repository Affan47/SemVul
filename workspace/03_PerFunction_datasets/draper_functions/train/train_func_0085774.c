jdwp_pack_u16( jdwp_buffer* buf, uint16_t word ){
	REQUIRE_CAP(2);
	*(uint16_t*)(buf->data + buf->len) = htons(word);
	buf->len += 2;
	return 0;
}
