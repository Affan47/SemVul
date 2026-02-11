conv_escape_str(char *str)
{
	int ch;
	char *cp;


	STARTSTACKSTR(cp);

	do {
		int c;

		ch = *str++;
		if (ch != '\\')
			continue;

		ch = *str++;
		if (ch == 'c') {

			ch = 0x100;
			continue;
		}


		if (ch == '0') {
			unsigned char i;
			i = 3;
			ch = 0;
			do {
				unsigned k = octtobin(*str);
				if (k > 7)
					break;
				str++;
				ch <<= 3;
				ch += k;
			} while (--i);
			continue;
		}


		str = conv_escape(str - 1, &c);
		ch = c;
	} while (STPUTC(ch, cp), (char)ch);

	return ch;
}
