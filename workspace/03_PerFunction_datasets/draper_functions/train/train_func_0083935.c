check_option(uint8_t code, uint8_t data_len)
{
	GDHCPOptionType type = dhcp_get_code_type(code);
	uint8_t len;

	if (type == OPTION_UNKNOWN)
		return type;

	len = dhcp_option_lengths[type & OPTION_TYPE_MASK];
	if (len != data_len) {
		printf("Invalid option len %d (expecting %d) for code 0x%x\n",
			data_len, len, code);
		return OPTION_UNKNOWN;
	}

	return type;
}
