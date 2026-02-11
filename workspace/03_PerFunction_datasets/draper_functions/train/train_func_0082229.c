vp2attr_rfc(const RADIUS_PACKET *packet,
			   const RADIUS_PACKET *original,
			   const char *secret, const VALUE_PAIR **pvp,
			   unsigned int attribute, uint8_t *ptr, size_t room)
{
	ssize_t len;

	if (room < 2) return 0;

	ptr[0] = attribute & 0xff;
	ptr[1] = 2;

	if (room > ((unsigned) 255 - ptr[1])) room = 255 - ptr[1];

	len = vp2data_any(packet, original, secret, 0, pvp, ptr + ptr[1], room);
	if (len <= 0) return len;

	ptr[1] += len;

#ifndef NDEBUG
	if ((fr_debug_flag > 3) && fr_log_fp) {
		fprintf(fr_log_fp, "\t\t%02x %02x  ", ptr[0], ptr[1]);
		print_hex_data(ptr + 2, len, 3);
	}
#endif

	return ptr[1];
}
