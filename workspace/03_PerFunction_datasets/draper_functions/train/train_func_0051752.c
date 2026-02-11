me_locops(struct Client *client_p, struct Client *source_p,
		int parc, const char *parv[])
{
	if(!IsPerson(source_p))
		return 0;

	if(find_shared_conf("*", "*", source_p->servptr->name, SHARED_LOCOPS))
		sendto_wallops_flags(UMODE_LOCOPS, source_p, "SLOCOPS - %s", parv[1]);

	return 0;
}
