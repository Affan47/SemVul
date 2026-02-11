expected_sysex_length(const unsigned char status, const unsigned char *second_byte, const size_t buffer_length, int32_t *consumed_bytes)
{
	uint32_t sysex_length = 0;
	uint32_t len = 0;

	assert(status == 0xF0);

	if (buffer_length < 3) {
		g_critical("SMF error: end of buffer in expected_sysex_length().");
		return (-1);
	}

	smf_extract_vlq(second_byte, buffer_length, &sysex_length, &len);

	if (consumed_bytes != NULL)
		*consumed_bytes = len;


	return (sysex_length + 1);
}
