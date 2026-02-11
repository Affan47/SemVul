pprint_tag(const unsigned char *sha1, const char *buf, unsigned long size)
{

	const char *endp = buf + size;
	const char *cp = buf;

	while (cp < endp) {
		char c = *cp++;
		if (c != '\n')
			continue;
		if (7 <= endp - cp && !memcmp("tagger ", cp, 7)) {
			const char *tagger = cp;


			write_or_die(1, buf, cp - buf);


			while (cp < endp) {
				if (*cp++ == '\n') {


					const char *sp = tagger;
					char *ep;
					unsigned long date;
					long tz;
					while (sp < cp && *sp != '>')
						sp++;
					if (sp == cp) {

						write_or_die(1, tagger,
							     cp - tagger);
						break;
					}
					while (sp < cp &&
					       !('0' <= *sp && *sp <= '9'))
						sp++;
					write_or_die(1, tagger, sp - tagger);
					date = strtoul(sp, &ep, 10);
					tz = strtol(ep, NULL, 10);
					sp = show_date(date, tz, 0);
					write_or_die(1, sp, strlen(sp));
					xwrite(1, "\n", 1);
					break;
				}
			}
			break;
		}
		if (cp < endp && *cp == '\n')

			break;
	}


	if (cp < endp)
		write_or_die(1, cp, endp - cp);
}
