fmtlen(unsigned char *s)
{
	int col = 0;
	struct utf8_sm sm;
	int c;

	utf8_init(&sm);

	while ((c= *s++)) {
		if (c == '\\') {
			switch (*s++) {
			case 'u':
			case 'i':
			case 'd':
			case 'f':
			case 'b':
			case 'U':
			case 'I':
			case 'D':
			case 'F':
			case 'B':
				continue;
			case 0:
				return col;
			default:
				++col;
				continue;
			}
		} else {
			int wid = 0;
			if(locale_map->type) {
				c = utf8_decode(&sm,c);
				if (c>=0)
					wid = joe_wcwidth(1,c);
			} else {
				wid = 1;
			}
			col += wid;
		}
	}
	return col;
}
