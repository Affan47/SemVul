num_pattern_p(const char *s)
{
    if (isdigit(*s))
	return 1;
    if (*s == '%') {
	s++;
	if (*s == 'E' || *s == 'O')
	    s++;
	if (*s &&
	    (strchr("CDdeFGgHIjkLlMmNQRrSsTUuVvWwXxYy", *s) || isdigit(*s)))
	    return 1;
    }
    return 0;
}
