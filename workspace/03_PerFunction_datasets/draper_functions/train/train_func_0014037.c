php_basename(char *s, size_t len, char *suffix, size_t sufflen, char **p_ret, size_t *p_len TSRMLS_DC)
{
	char *ret = NULL, *c, *comp, *cend;
	size_t inc_len, cnt;
	int state;

	c = comp = cend = s;
	cnt = len;
	state = 0;
	while (cnt > 0) {
		inc_len = (*c == '\0' ? 1: php_mblen(c, cnt));

		switch (inc_len) {
			case -2:
			case -1:
				inc_len = 1;
				php_mblen(NULL, 0);
				break;
			case 0:
				goto quit_loop;
			case 1:
#if defined(PHP_WIN32) || defined(NETWARE)
				if (*c == '/' || *c == '\\') {
#else
				if (*c == '/') {
#endif
					if (state == 1) {
						state = 0;
						cend = c;
					}
				} else {
					if (state == 0) {
						comp = c;
						state = 1;
					}
				}
				break;
			default:
				if (state == 0) {
					comp = c;
					state = 1;
				}
				break;
		}
		c += inc_len;
		cnt -= inc_len;
	}

quit_loop:
	if (state == 1) {
		cend = c;
	}
	if (suffix != NULL && sufflen < (uint)(cend - comp) &&
			memcmp(cend - sufflen, suffix, sufflen) == 0) {
		cend -= sufflen;
	}

	len = cend - comp;

	if (p_ret) {
		ret = emalloc(len + 1);
		memcpy(ret, comp, len);
		ret[len] = '\0';
		*p_ret = ret;
	}
	if (p_len) {
		*p_len = len;
	}
}
