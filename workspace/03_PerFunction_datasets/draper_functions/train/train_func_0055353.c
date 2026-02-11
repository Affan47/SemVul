parse_author(const char *from, long *len)
{
    const char	*c1, *c2;

    if ((c2 = strchr(from, '<'))) {
	c1 = from;
	while (c1 < c2 && (IS_SPACE(*c1) || *c1 == '"'))
	    c1++;
	do {
	    c2--;
	} while (c2 > c1 && (IS_SPACE(*c2) || *c2 == '"'));

	*len = c2 - c1 + 1;
	if (*len > 0)
	    return c1;
    }

    if ((c1 = strchr(from, '(')) && (c2 = strrchr(c1, ')'))) {
	do {
	    c1++;
	} while (c1 < c2 && (IS_SPACE(*c1) || *c1 == '"'));
	do {
	    c2--;
	} while (c2 > c1 && (IS_SPACE(*c2) || *c2 == '"'));

	*len = c2 - c1 + 1;
	if (*len > 0)
	    return c1;
    }

    c1 = from;
    while (IS_SPACE(*c1))
	c1++;
    if (*c1 != '\0') {
	c2 = c1 + strlen(c1);
	do {
	    c2--;
	} while (c2 > c1 && IS_SPACE(*c1));

	*len = c2 - c1 + 1;
	if (*len > 0)
	    return c1;
    }

    *len = 6;
    return "<none>";
}
