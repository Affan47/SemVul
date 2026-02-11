scan_numfile(char *s, unsigned int first, unsigned int last) {
	int num = 0;
	unsigned char c;

	while ((c = *s) != NUL && isdigit(c)) {
		num = num * 10 + c - '0';
		s++;
	}

	if (num == 0)
		return FALSE;
	else if (*s == NUL)
		;
	else if (strncmp(s, Suffix, Suffix_len) == 0 && s[Suffix_len] == NUL)
		;
	else
		return FALSE;

	if (num >= first && (last == 0 || num <= last))
		return TRUE;
        else
                return FALSE;
}
