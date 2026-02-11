vmod_duration(struct sess *sp, const char *p, double d)
{
	char *e;
	double r;

	(void)sp;

	if (p == NULL)
		return (d);

	while(isspace(*p))
		p++;

	if (*p != '+' && *p != '-' && !isdigit(*p))
		return (d);

	e = NULL;

	r = strtod(p, &e);

	if (!isfinite(r))
		return (d);

	if (e == NULL)
		return (d);

	while(isspace(*e))
		e++;


	switch (*e++) {
	case 's': break;
	case 'm': r *= 60.; break;
	case 'h': r *= 60.*60.; break;
	case 'd': r *= 60.*60.*24.; break;
	case 'w': r *= 60.*60.*24.*7.; break;
	default:
		return (d);
	}

	while(isspace(*e))
		e++;

	if (*e != '\0')
		return (d);

	return (r);
}
