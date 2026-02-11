to_binary(char *str, STRLEN *outlen) {
	CS_BINARY *b, *b_ptr;
	char s[3], *strtol_end;
	STRLEN i, b_len;
	long int x;


	if (str[0] == '0' && str[1] == 'x')
		str += 2;


	b_len = (strlen(str) + 1) / 2;
	b = (CS_BINARY *) safemalloc(b_len);
	memset(b, 0, b_len);
	memset(&s, '\0', 3);


	b_ptr = b;
	for (i = 0; i < b_len; i++, str += 2) {
		strncpy(s, str, 2);
		x = strtol(s, &strtol_end, 16);
		if (*strtol_end != '\0') {
			warn("conversion failed: invalid char '%c'", *strtol_end);
			break;
		}
		*b_ptr++ = x;
	}
	*outlen = b_len;

	return b;
}
