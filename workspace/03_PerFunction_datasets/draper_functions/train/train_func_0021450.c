parse__escape(const Char **ptr)
{
	const Char *p;
	Int c;

	p = *ptr;

	if (p[1] == 0)
		return -1;

	if (*p == '\\') {
		p++;
		switch (*p) {
		case 'a':
			c = '\007';
			break;
		case 'b':
			c = '\010';
			break;
		case 't':
			c = '\011';
			break;
		case 'n':
			c = '\012';
			break;
		case 'v':
			c = '\013';
			break;
		case 'f':
			c = '\014';
			break;
		case 'r':
			c = '\015';
			break;
		case 'e':
			c = '\033';
			break;
                case 'U':
                {
                        int i;
                        const Char hex[] = STR("0123456789ABCDEF");
                        const Char *h;
                        ++p;
                        if (*p++ != '+')
                                return -1;
			c = 0;
                        for (i = 0; i < 5; ++i) {
                                h = Strchr(hex, *p++);
                                if (!h && i < 4)
                                        return -1;
                                else if (h)
                                        c = (c << 4) | ((int)(h - hex));
                                else
                                        --p;
                        }
                        if (c > 0x10FFFF)
                                return -1;
                        break;
                }
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		{
			int cnt, ch;

			for (cnt = 0, c = 0; cnt < 3; cnt++) {
				ch = *p++;
				if (ch < '0' || ch > '7') {
					p--;
					break;
				}
				c = (c << 3) | (ch - '0');
			}
			if ((c & (wint_t)0xffffff00) != (wint_t)0)
				return -1;
			--p;
			break;
		}
		default:
			c = *p;
			break;
		}
	} else if (*p == '^') {
		p++;
		c = (*p == '?') ? '\177' : (*p & 0237);
	} else
		c = *p;
	*ptr = ++p;
	return c;
}
