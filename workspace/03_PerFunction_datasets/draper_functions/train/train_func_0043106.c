_nc_msec_cost(const char *const cap, int affcnt)

{
    if (cap == 0)
	return (INFINITY);
    else {
	const char *cp;
	float cum_cost = 0.0;

	for (cp = cap; *cp; cp++) {

	    if (cp[0] == '$' && cp[1] == '<' && strchr(cp, '>')) {
		float number = 0.0;

		for (cp += 2; *cp != '>'; cp++) {
		    if (isdigit(UChar(*cp)))
			number = number * 10 + (*cp - '0');
		    else if (*cp == '*')
			number *= affcnt;
		    else if (*cp == '.' && (*++cp != '>') && isdigit(UChar(*cp)))
			number += (*cp - '0') / 10.0;
		}

#if NCURSES_NO_PADDING
		if (!GetNoPadding(SP))
#endif
		    cum_cost += number * 10;
	    } else
		cum_cost += SP->_char_padding;
	}

	return ((int) cum_cost);
    }
}
