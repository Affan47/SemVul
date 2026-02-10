get_client_host(aClient *cptr)
{
	static char nbuf[HOSTLEN * 2 + USERLEN + 5];

	if (!MyConnect(cptr))
		return cptr->name;
	if (!cptr->user)
		return get_client_name(cptr, TRUE);
#ifdef UNIXPORT
	if (IsUnixSocket(cptr))
		sprintf(nbuf, "%s[%s]", cptr->name, ME);
	else
#endif
		(void)sprintf(nbuf, "%s[%-.*s@%-.*s]",
			cptr->name, USERLEN,
			(!(cptr->flags & FLAGS_GOTID)) ? "" : cptr->auth,
			HOSTLEN, cptr->user->sip);
	return nbuf;
}
