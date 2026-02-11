opt__P(type, s)
	int type;
	register char *s;
{
	register char **proto;
	PARG parg;

	switch (type)
	{
	case INIT:
	case TOGGLE:


		switch (*s)
		{
		case 's':  proto = &prproto[PR_SHORT];	s++;	break;
		case 'm':  proto = &prproto[PR_MEDIUM];	s++;	break;
		case 'M':  proto = &prproto[PR_LONG];	s++;	break;
		case '=':  proto = &eqproto;		s++;	break;
		case 'h':  proto = &hproto;		s++;	break;
		case 'w':  proto = &wproto;		s++;	break;
		default:   proto = &prproto[PR_SHORT];		break;
		}
		free(*proto);
		*proto = save(s);
		break;
	case QUERY:
		parg.p_string = prproto[pr_type];
		error("%s", &parg);
		break;
	}
}
