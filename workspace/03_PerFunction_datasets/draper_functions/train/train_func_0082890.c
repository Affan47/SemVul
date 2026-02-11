imap_response_parse(void)
{
	static char	*parsebuf;
	static size_t	parsebufsize;
	const char	*ip = imapbuf;
	char	*pp;

	if (parsebufsize < imapbufsize) {
		free(parsebuf);
		parsebuf = smalloc(parsebufsize = imapbufsize);
	}
	strcpy(parsebuf, imapbuf);
	pp = parsebuf;
	switch (*ip) {
	case '+':
		response_type = RESPONSE_CONT;
		ip++;
		pp++;
		while (*ip == ' ') {
			ip++;
			pp++;
		}
		break;
	case '*':
		ip++;
		pp++;
		while (*ip == ' ') {
			ip++;
			pp++;
		}
		imap_response_get(&ip);
		pp = &parsebuf[ip - imapbuf];
		switch (response_status) {
		case RESPONSE_BYE:
			response_type = RESPONSE_FATAL;
			break;
		default:
			response_type = RESPONSE_DATA;
		}
		break;
	default:
		responded_tag = parsebuf;
		while (*pp && *pp != ' ')
			pp++;
		if (*pp == '\0') {
			response_type = RESPONSE_ILLEGAL;
			break;
		}
		*pp++ = '\0';
		while (*pp && *pp == ' ')
			pp++;
		if (*pp == '\0') {
			response_type = RESPONSE_ILLEGAL;
			break;
		}
		ip = &imapbuf[pp - parsebuf];
		response_type = RESPONSE_TAGGED;
		imap_response_get(&ip);
		pp = &parsebuf[ip - imapbuf];
	}
	responded_text = pp;
	if (response_type != RESPONSE_CONT &&
			response_type != RESPONSE_ILLEGAL &&
			response_status == RESPONSE_OTHER)
		imap_other_get(pp);
}
