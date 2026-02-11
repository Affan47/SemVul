utf8_canonize(const char *src)
{
	uint32 *dst32;

	g_assert(utf8_is_valid_string(src));

	{
		size_t n;
		uint32 buf[1024];
		uint32 *s;

		n = utf8_to_utf32(src, buf, G_N_ELEMENTS(buf));
		if (n < G_N_ELEMENTS(buf)) {
			s = buf;
		} else {
			size_t size = n + 1;

			HALLOC_ARRAY(s, size);
			n = utf8_to_utf32(src, s, size);
			g_assert(size - 1 == n);
		}

		dst32 = utf32_canonize(s);
		g_assert(dst32 != s);
		if (s != buf) {
			HFREE_NULL(s);
		}
	}

	(void) utf32_to_utf8_inplace(dst32);
	return cast_to_char_ptr(dst32);
}
