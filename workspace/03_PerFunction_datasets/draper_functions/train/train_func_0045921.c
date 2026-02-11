check_utf8_char_type(unsigned char *ucp)
{
    int code = 0;
    int length = strlen(ucp);
    int unicode;

    unsigned char c = *ucp;
    if (c > 0xfb) {
	code = 0;
    }
    else if (c > 0xf7) {
	code = 0;
    }
    else if (c > 0xef) {
	code = 0;
    }
    else if (c > 0xdf) {
	unicode = (c & 0x0f) << 12;
	c = *(ucp + 1);
	unicode += (c & 0x3f) << 6;
	c = *(ucp + 2);
	unicode += c & 0x3f;
	code = check_unicode_char_type(unicode);
    }
    else if (c > 0x7f) {
	unicode = (c & 0x1f) << 6;
	c = *(ucp + 1);
	unicode += c & 0x3f;
	code = check_unicode_char_type(unicode);
    }
    else {
	code = check_unicode_char_type(c);
    }

    return code;
}
