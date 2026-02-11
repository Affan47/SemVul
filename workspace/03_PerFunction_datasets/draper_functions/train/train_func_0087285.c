assemble_ethernet_header (interface, buf, bufix, to)
	struct interface_info *interface;
	unsigned char *buf;
	unsigned *bufix;
	struct hardware *to;
{
	struct isc_ether_header eh;

	if (to && to -> hlen == 7)
		memcpy (eh.ether_dhost, &to -> hbuf [1],
			sizeof eh.ether_dhost);
	else
		memset (eh.ether_dhost, 0xff, sizeof (eh.ether_dhost));
	if (interface -> hw_address.hlen - 1 == sizeof (eh.ether_shost))
		memcpy (eh.ether_shost, &interface -> hw_address.hbuf [1],
			sizeof (eh.ether_shost));
	else
		memset (eh.ether_shost, 0x00, sizeof (eh.ether_shost));

	eh.ether_type = htons (ETHERTYPE_IP);

	memcpy (&buf [*bufix], &eh, ETHER_HEADER_SIZE);
	*bufix += ETHER_HEADER_SIZE;
}
