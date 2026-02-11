hex_encode_alloc(const uint8_t  *in,
                            const uint32_t in_len,
                            uint8_t        **out)
{
	uint32_t out_len = 2 * in_len;


	*out = malloc(out_len);

	if (*out == NULL) {
		return -1;
	}


	return hex_encode(in, in_len, *out, out_len);
}
