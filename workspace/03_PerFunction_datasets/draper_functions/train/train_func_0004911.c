DeTab(src, start_offset, dst, dst_limit, visspace)
char	*src;
int	start_offset;
char	*dst;
char	*dst_limit;
bool	visspace;
{
	ZXchar	c;
	int	offset = start_offset;


#define addc(ch) { if (--offset < 0) *dst++ = (ch); }

	while ((c = ZXC(*src++)) != '\0') {
		if (c == '\t' && tabstop != 0) {
			int	nchars = TABDIST(start_offset - offset);

			c = visspace? '>' : ' ';
			while (--nchars > 0 && dst < dst_limit) {
				addc(c);
				c = ' ';
			}
		} else if (jisprint(c)) {
			if (visspace && c == ' ')
				c = '_';
		} else {
			char	buf[PPWIDTH];
			char	*p;

			PPchar(c, buf);

			for (p = buf; (c = *p++), *p != '\0'; )
				addc(c);
		}
		if (--offset < 0) {
			*dst++ = c;
			if (dst >= dst_limit) {

				dst = dst_limit-1;
				*dst++ = '!';
				break;
			}
		}
	}
#undef	addc
	*dst = '\0';
}
