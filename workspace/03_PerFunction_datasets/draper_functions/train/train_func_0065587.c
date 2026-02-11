ms_locops(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{


	propagate_generic(source_p, "LOCOPS", parv[1], CAP_CLUSTER,
				":%s", parv[2]);

	if(!match(parv[1], me.name))
		return 0;

	if(find_shared_conf("*", "*", source_p->servptr->name, SHARED_LOCOPS))
		sendto_wallops_flags(UMODE_LOCOPS, source_p, "SLOCOPS - %s", parv[2]);

	return 0;
}
