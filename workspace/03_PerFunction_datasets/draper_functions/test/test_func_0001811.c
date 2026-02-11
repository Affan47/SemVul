str_trim_trailing_zeros (char *s, gboolean leave_first_zero)
{
	char *p, *pp;

	p = strrchr(s,'.');
	if(!p) return;

	if (leave_first_zero &&
	    *(p+1) == '0') {
		p = p+2;
		pp = p;
	} else {
		pp=p+1;
	}
	for (; *pp != '\0'; pp++) {
		if (*pp != '0')
			p = pp+1;
	}
	*p = '\0';
}
