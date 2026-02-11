append_signoff(char *buf, int buf_sz, int at, const char *signoff)
{
	static const char signed_off_by[] = "Signed-off-by: ";
	int signoff_len = strlen(signoff);
	int has_signoff = 0;
	char *cp = buf;


	if (buf_sz - at <= strlen(signed_off_by) + signoff_len + 3)
		return at;


	while ((cp = strstr(cp, signed_off_by))) {

		has_signoff = 1;

		cp += strlen(signed_off_by);
		if (cp + signoff_len >= buf + at)
			break;
		if (strncmp(cp, signoff, signoff_len))
			continue;
		if (!isspace(cp[signoff_len]))
			continue;

		return at;
	}

	if (!has_signoff)
		has_signoff = detect_any_signoff(buf, at);

	if (!has_signoff)
		buf[at++] = '\n';

	strcpy(buf + at, signed_off_by);
	at += strlen(signed_off_by);
	strcpy(buf + at, signoff);
	at += signoff_len;
	buf[at++] = '\n';
	buf[at] = 0;
	return at;
}
