mo_adminresv(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(!IsOperResv(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS), me.name, source_p->name, "resv");
		return 0;
	}

	if(!IsOperAdmin(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS), me.name, source_p->name, "admin");
		return 0;
	}

	parse_resv(source_p, parv[1], parv[2], 0, 1);

	return 0;
}
