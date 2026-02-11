filepathutil_strippath(ucs2_char_t* path)
{
	ucs2_char_t* p = path + ucs2len(path) - 1;
	if (path <= p) {
		if (*p == PATHCHAR) {
			p--;
		}
		while (path <= p) {
			if (*p == PATHCHAR) {
				p++;
				break;
			}
			p--;
		}
		if (path < p) {
			for (;;) {
				*path = *p;
				if (!*p) {
					break;
				}
				path++;
				p++;
			}
		}
	}
}
