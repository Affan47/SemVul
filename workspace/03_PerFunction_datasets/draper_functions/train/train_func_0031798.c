find_matching_client(char *mask)
{
	aClient *acptr;
	aServer *asptr;
	aService *sp;
	char *ch;
	int wild = 0, dot = 0;


	acptr = find_client(mask, NULL);

	if (acptr)
	{
		return acptr;
	}

	for (ch = mask; *ch; ch++)
	{
		if (*ch == '*' || *ch == '?')
		{
			wild = 1;
			break;
		}
		if (*ch == '.')
		{
			dot = 1;
			break;
		}
	}

	if (!wild && !dot)
	{
		return NULL;
	}

	(void) collapse(mask);


	for (asptr = me.serv; asptr; asptr = asptr->prevs)
	{
		if (!match(asptr->bcptr->name, mask) ||
		    !match(mask, asptr->bcptr->name))
		{
			acptr = asptr->bcptr;
			return acptr->serv->maskedby;
		}
	}

	for (sp = svctop; sp; sp = sp->nexts)
	{
		if (!match(sp->bcptr->name, mask) ||
		    !match(mask, sp->bcptr->name))
		{
			acptr = sp->bcptr;
			return acptr;
		}
	}
	return NULL;
}
