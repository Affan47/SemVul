php_filter_encode_url(zval *value, const unsigned char* chars, const int char_len, int high, int low, int encode_nul)
{
	unsigned char *str, *p;
	unsigned char tmp[256];
	unsigned char *s = (unsigned char *)chars;
	unsigned char *e = s + char_len;

	memset(tmp, 1, sizeof(tmp)-1);

	while (s < e) {
		tmp[*s++] = 0;
	}


	p = str = (unsigned char *) safe_emalloc(3, Z_STRLEN_P(value), 1);
	s = (unsigned char *)Z_STRVAL_P(value);
	e = s + Z_STRLEN_P(value);

	while (s < e) {
		if (tmp[*s]) {
			*p++ = '%';
			*p++ = hexchars[(unsigned char) *s >> 4];
			*p++ = hexchars[(unsigned char) *s & 15];
		} else {
			*p++ = *s;
		}
		s++;
	}
	*p = '\0';
	str_efree(Z_STRVAL_P(value));
	Z_STRVAL_P(value) = (char *)str;
	Z_STRLEN_P(value) = p - str;
}
