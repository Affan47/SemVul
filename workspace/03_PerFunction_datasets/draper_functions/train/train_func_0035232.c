is_number(char *s)
{
	double r;
	char *ep;


	switch (*s) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ' ':
	case '-':
	case '+':
	case '.':
	case 'n':
	case 'N':
	case 'i':
	case 'I':
		break;
	default:
		return 0;
	}

	errno = 0;
	r = strtod(s, &ep);
	if (ep == s || r == HUGE_VAL || errno == ERANGE)
		return 0;
	while (*ep == ' ' || *ep == '\t' || *ep == '\n')
		ep++;
	if (*ep == '\0')
		return 1;
	else
		return 0;
}
