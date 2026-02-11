evalcodeselect(w, c)
int w, c;
{
	if (c >= ' ' && c <= '/') {
		if (pty[w].nchar < MAXESCCHAR)
			pty[w].escchar[(pty[w].nchar)++] = c;
		return;
	}

	if (c < 0x30 || c > 0x7e) return;

	switch (pty[w].escmode) {
		case '$':
			if (pty[w].nchar > (u_char)1 || (pty[w].nchar
			&& (pty[w].escchar[0] < '('
			|| pty[w].escchar[0] > '+'))) {
				pty[w].escmode = '\0';
				return;
			}
			pty[w].termflags |= T_MULTIBYTE;
			break;
		default:
			if (pty[w].nchar) {
				pty[w].escmode = '\0';
				return;
			}
			pty[w].termflags &= ~T_MULTIBYTE;
			break;
	}

	pty[w].codeselect[0] = pty[w].escmode;
	memcpy(&(pty[w].codeselect[1]), (char *)(pty[w].escchar),
		pty[w].nchar);
	pty[w].codeselect[++(pty[w].nchar)] = c;
	pty[w].codeselect[++(pty[w].nchar)] = '\0';

	pty[w].escmode = '\0';
}
