vmsg_advertise_udp_compression(gnutella_header_t *header)
{
	uint8 ttl = gnutella_header_get_ttl(header);

	g_assert(0 == (ttl & GTA_UDP_CAN_INFLATE));

	gnutella_header_set_ttl(header, ttl | GTA_UDP_CAN_INFLATE);
}
