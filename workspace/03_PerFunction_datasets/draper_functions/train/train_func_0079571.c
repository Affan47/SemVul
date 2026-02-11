dhcpv6_add_binary_option(struct dhcpv6_packet *packet, uint16_t max_len,
				uint16_t *pkt_len, uint8_t *addopt)
{
	unsigned len;
	uint8_t *optionptr = packet->options;

	len = 2 + 2 + (addopt[2] << 8 | addopt[3]);


	if (*pkt_len + len >= max_len)

		return;

	memcpy(optionptr + *pkt_len, addopt, len);
	*pkt_len += len;
}
