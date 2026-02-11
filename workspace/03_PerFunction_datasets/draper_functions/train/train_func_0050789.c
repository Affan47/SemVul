is_ipmi_channel_num(const char *argv_ptr, uint8_t *channel_ptr)
{
	if (!argv_ptr || !channel_ptr) {
		lprintf(LOG_ERR,
				"is_ipmi_channel_num(): invalid argument(s).");
		return (-1);
	}
	if ((str2uchar(argv_ptr, channel_ptr) == 0)
			&& ((*channel_ptr >= 0x0 && *channel_ptr <= 0x7)
				|| (*channel_ptr >= 0xE && *channel_ptr <= 0xF))) {
		return 0;
	}
	lprintf(LOG_ERR,
			"Given Channel number '%s' is either invalid or out of range.",
			argv_ptr);
	lprintf(LOG_ERR, "Channel number must be from ranges: <0..7>, <0xE..0xF>");
	return (-1);
}
