utf8_canonical_sorted(const char *src)
{
	uint prev, cc;
	char c;

	for (prev = 0; '\0' != (c = *src); prev = cc) {
		if (UTF8_IS_ASCII(c)) {
			src++;
			cc = 0;
		} else {
			uint32 uc;
			uint retlen;

			uc = utf8_decode_char_fast(src, &retlen);
			if (uc == 0x0000)
				break;

			cc = utf32_combining_class(uc);
			if (cc != 0 && prev > cc)
				return FALSE;

			src += retlen;
		}
	}

	return TRUE;
}
