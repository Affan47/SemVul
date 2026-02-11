m_servlist(aClient *cptr, aClient *sptr, int parc, char *parv[])
{
	Reg	aService *sp;
	Reg	aClient *acptr;
	char	*mask = BadPtr(parv[1]) ? "*" : parv[1];
	int	type = 0;

	if (parc > 2)
		type = BadPtr(parv[2]) ? 0 : strtol(parv[2], NULL, 0);
	for (sp = svctop; sp; sp = sp->nexts)
		if  ((acptr = sp->bcptr) && (!type || type == sp->type) &&
		     (match(mask, acptr->name) == 0))
			sendto_one(sptr, replies[RPL_SERVLIST], ME, BadTo(parv[0]),
				   acptr->name, sp->server, sp->dist,
				   sp->type, acptr->hopcount, acptr->info);
	sendto_one(sptr, replies[RPL_SERVLISTEND], ME, BadTo(parv[0]), mask, type);
	return 2;
}
