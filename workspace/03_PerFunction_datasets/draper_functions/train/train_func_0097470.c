vsxxxaa_smells_like_packet(struct vsxxxaa *mouse,
					     unsigned char type, size_t len)
{
	return mouse->count >= len && MATCH_PACKET_TYPE(mouse->buf[0], type);
}
