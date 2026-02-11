utf32_remap(uint32 *dst, const uint32 *src, size_t size,
	utf32_remap_func remap)
{
	const uint32 *s = src;
	uint32 *p = dst;

	g_assert(dst != NULL);
	g_assert(src != NULL);
	g_assert(remap != NULL);
	g_assert(size <= INT_MAX);

	if (size > 0) {
		uint32 *end, uc;

		end = &dst[size - 1];

		if (size > UTF8_CPU_CACHELINE) {
			for (p = dst; p != end && 0x0000 != (uc = *s); p++, s++) {
				G_PREFETCH_R(&s[UTF8_CPU_CACHELINE / sizeof *s]);
				G_PREFETCH_W(&p[UTF8_CPU_CACHELINE / sizeof *p]);
				*p = remap(uc);
			}
		} else {
			for (p = dst; p != end && 0x0000 != (uc = *s); p++, s++) {
				*p = remap(uc);
			}
		}
		*p = 0x0000;
	}

	if (0x0000 != *s)
		p += utf32_strlen(s);

	return p - dst;
}
