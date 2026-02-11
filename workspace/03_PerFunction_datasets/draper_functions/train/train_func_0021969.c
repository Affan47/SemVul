verify_header(const uint8_t *buf)
{
	memcpy(&header, buf, sizeof(header));

	if (le32_to_cpu(header.validation) != VALIDATION_WORD)
		return -1;
	if (le16_to_cpu(header.checksum) != hdr_checksum(&header))
		return -1;

	return le16_to_cpu(header.length_u32) * 4;
}
