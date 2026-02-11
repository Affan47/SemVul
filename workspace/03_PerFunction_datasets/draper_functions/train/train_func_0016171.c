shellecho(const char *cp)
{
	int	cflag = 0, n;
	char	c;

	while (*cp) {
		if (*cp == '\\') {
			switch (*++cp) {
			case '\0':
				return cflag;
			case 'a':
				putchar('\a');
				break;
			case 'b':
				putchar('\b');
				break;
			case 'c':
				cflag = 1;
				break;
			case 'f':
				putchar('\f');
				break;
			case 'n':
				putchar('\n');
				break;
			case 'r':
				putchar('\r');
				break;
			case 't':
				putchar('\t');
				break;
			case 'v':
				putchar('\v');
				break;
			default:
				putchar(*cp&0377);
				break;
			case '0':
				c = 0;
				n = 3;
				while (n-- && octalchar(cp[1]&0377)) {
					c <<= 3;
					c |= cp[1] - '0';
					cp++;
				}
				putchar(c);
			}
		} else
			putchar(*cp & 0377);
		cp++;
	}
	return cflag;
}
