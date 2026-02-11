get_filepart(ucs2_char_t *dst, size_t mbs_size, ucs2_char_t* src, size_t ucs_size)
{
	ucs2_char_t *wcstr = ucs2dup(src);
	ucs2_char_t *p = ucs2rchr(wcstr, 0x005C);
	if (p) {
		p++;
	} else {
		p = wcstr;
	}
	ucs2cpy(dst, p);
	return dst;
}
