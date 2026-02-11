xml_utf8_decode(const XML_Char *s, int len, int *newlen, const XML_Char *encoding)
{
	int pos = len;
	char *newbuf = emalloc(len + 1);
	unsigned int c;
	char (*decoder)(unsigned short) = NULL;
	xml_encoding *enc = xml_get_encoding(encoding);

	*newlen = 0;
	if (enc) {
		decoder = enc->decoding_function;
	}
	if (decoder == NULL) {


		memcpy(newbuf, s, len);
		*newlen = len;
		newbuf[*newlen] = '\0';
		return newbuf;
	}
	while (pos > 0) {
		c = (unsigned char)(*s);
		if (c >= 0xf0) {
			if(pos-4 >= 0) {
				c = ((s[0]&7)<<18) | ((s[1]&63)<<12) | ((s[2]&63)<<6) | (s[3]&63);
			} else {
				c = '?';
			}
			s += 4;
			pos -= 4;
		} else if (c >= 0xe0) {
			if(pos-3 >= 0) {
				c = ((s[0]&63)<<12) | ((s[1]&63)<<6) | (s[2]&63);
			} else {
				c = '?';
			}
			s += 3;
			pos -= 3;
		} else if (c >= 0xc0) {
			if(pos-2 >= 0) {
				c = ((s[0]&63)<<6) | (s[1]&63);
			} else {
				c = '?';
			}
			s += 2;
			pos -= 2;
		} else {
			s++;
			pos--;
		}
		newbuf[*newlen] = decoder ? decoder(c) : c;
		++*newlen;
	}
	if (*newlen < len) {
		newbuf = erealloc(newbuf, *newlen + 1);
	}
	newbuf[*newlen] = '\0';
	return newbuf;
}
