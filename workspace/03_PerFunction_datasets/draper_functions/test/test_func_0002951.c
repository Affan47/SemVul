init_special_char(char* arg, struct options *op)
{
	char ch, *p, *q;
	int i;

	op->initstring = malloc(strlen(arg) + 1);
	if (!op->initstring)
		log_err(_("failed to allocate memory: %m"));


	q = op->initstring;
	p = arg;
	while (*p) {

		if (*p == '\\') {
			p++;
			if (*p == '\\') {
				ch = '\\';
				p++;
			} else {

				ch = 0;
				for (i = 1; i <= 3; i++) {
					if (*p >= '0' && *p <= '7') {
						ch <<= 3;
						ch += *p - '0';
						p++;
					} else {
						break;
					}
				}
			}
			*q++ = ch;
		} else
			*q++ = *p++;
	}
	*q = '\0';
}
