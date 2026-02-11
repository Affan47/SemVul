read_header(FILE *in, struct coff_header *hdr)
{
	uint8_t hdr_data[FILE_HEADER_SIZE];

	if (read_block(in, 0, FILE_HEADER_SIZE, hdr_data) < 0) {
		printc_err("coff: failed to extract COFF header\n");
		return -1;
	}

	parse_header(hdr_data, hdr);
	return 0;
}
