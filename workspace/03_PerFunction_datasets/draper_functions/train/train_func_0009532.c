potential_number_p(strng, base)
object strng;
int base;
{
	int i, l, c, dc;
	char *s;

	l = strng->st.st_fillp;
	if (l == 0)
		return(FALSE);
	s = strng->st.st_self;
	dc = 0;
	c = s[0];
	if (digitp(c, base) >= 0)
		dc++;
	else if (c != '+' && c != '-' && c != '^' && c != '_')
		return(FALSE);
	if (s[l-1] == '+' || s[l-1] == '-')
		return(FALSE);
	for (i = 1;  i < l;  i++) {
		c = s[i];
		if (digitp(c, base) >= 0) {
			dc++;
			continue;
		}
		if (c != '+' && c != '-' && c != '/' && c != '.' &&
		    c != '^' && c != '_' &&
		    c != 'e' && c != 'E' &&
		    c != 's' && c != 'S' && c != 'l' && c != 'L')
			return(FALSE);
	}
	if (dc == 0)
		return(FALSE);
	return(TRUE);
}
