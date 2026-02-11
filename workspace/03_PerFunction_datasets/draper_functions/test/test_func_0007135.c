check_broken_vendor(struct dhcp_packet *packet)
{
	uint8_t *vendor;

	if (packet->op != BOOTREQUEST)
		return;

	vendor = dhcp_get_option(packet, DHCP_VENDOR);
	if (vendor == NULL)
		return;

	if (check_vendor(vendor, "MSFT 98") == TRUE)
		packet->flags |= htons(BROADCAST_FLAG);
}
