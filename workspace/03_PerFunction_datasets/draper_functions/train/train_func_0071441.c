utf8_remap(char *dst, const char *src, size_t size, utf32_remap_func remap)
{
	uint32 uc;
	uint32 nuc;
	uint retlen;
	size_t new_len;

	g_assert(size == 0 || dst != NULL);
	g_assert(src != NULL);
	g_assert(remap != NULL);
	g_assert(size <= INT_MAX);


#define LOOP_BODY										\
	uc = utf8_decode_char_fast(src, &retlen);			\
	if (uc == 0x0000)									\
		break;											\
														\
	nuc = remap(uc);									\
	if (nuc == uc) {									\
		if (retlen > size)								\
			break;										\
														\
		size -= retlen;									\
		while (retlen-- > 0)							\
			*dst++ = *src++;							\
	} else {											\
		uint utf8_len;									\
														\
		utf8_len = utf8_encode_char(nuc, dst, size);	\
		if (utf8_len == 0 || utf8_len > size)			\
			break;										\
														\
		src += retlen;									\
		dst += utf8_len;								\
		size -= utf8_len;								\
	}

	if (size <= 0) {
		new_len = 0;
	} else {
		const char *dst0 = dst;

		size--;

		if (size > UTF8_CPU_CACHELINE) {

			while (*src != '\0') {
				G_PREFETCH_R(&src[UTF8_CPU_CACHELINE]);
				G_PREFETCH_W(&dst[UTF8_CPU_CACHELINE]);

				LOOP_BODY
			}
		} else {

			while (*src != '\0') {
				LOOP_BODY
			}
		}
		new_len = dst - dst0;
		*dst = '\0';
	}

#undef LOOP_BODY

	while (*src != '\0') {
		G_PREFETCH_R(&src[UTF8_CPU_CACHELINE]);

		uc = utf8_decode_char_fast(src, &retlen);
		if (uc == 0x0000)
			break;

		src += retlen;
		nuc = remap(uc);
		new_len += nuc == uc ? retlen : uniskip(nuc);
	}

	return new_len;
}
