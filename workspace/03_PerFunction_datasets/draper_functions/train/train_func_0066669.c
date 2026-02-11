string2hex(const unsigned char *buf, int buf_len, char **hexbuf, int *hexbuf_len)
{
    static const char hex[]="0123456789abcdef";
    int i, len = 2 * buf_len;

    if (buf_len < 0 || len < buf_len) {
	return -1;
    }
    if (!hexbuf) {
	if (hexbuf_len) {
	    *hexbuf_len = len;
	}
	return len;
    }
    if (!(*hexbuf = OPENSSL_malloc(len + 1))) {
	return -1;
    }
    for (i = 0; i < buf_len; i++) {
	(*hexbuf)[2 * i] = hex[((unsigned char)buf[i]) >> 4];
	(*hexbuf)[2 * i + 1] = hex[buf[i] & 0x0f];
    }
    (*hexbuf)[2 * i] = '\0';

    if (hexbuf_len) {
	*hexbuf_len = len;
    }
    return len;
}
