do_lzo_compress(void)
{
	header_t header;

#define h (&header)
	memset(h, 0, sizeof(*h));

	lzo_set_method(h);

	h->version = (LZOP_VERSION & 0xffff);
	h->version_needed_to_extract = 0x0940;
	h->lib_version = lzo_version() & 0xffff;

	h->flags = (F_OS & F_OS_MASK) | (F_CS & F_CS_MASK);

	if (!(option_mask32 & OPT_F) || h->method == M_LZO1X_999) {
		h->flags |= F_ADLER32_D;
		if (option_mask32 & OPT_C)
			h->flags |= F_ADLER32_C;
	}
	write_header(h);
	return lzo_compress(h);
#undef h
}
