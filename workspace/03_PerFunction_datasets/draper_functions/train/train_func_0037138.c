is_header(void *data, size_t size) {

	struct header * hdr = data;

	if ( size < sizeof(struct header) )
		return 0;

	if ( memcmp(hdr->magic, HDR_MAGIC, sizeof(hdr->magic)) != 0 )

		return 0;
	return 1;

}
