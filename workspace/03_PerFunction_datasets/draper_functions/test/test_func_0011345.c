mo_modrestart(struct Client *client_p, struct Client *source_p, int parc, const char **parv)
{
	int modnum;

	if(!IsOperAdmin(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS),
			   me.name, source_p->name, "admin");
		return 0;
	}

	sendto_one_notice(source_p, ":Reloading all modules");

	modnum = num_mods;
	while (num_mods)
		unload_one_module(modlist[0]->name, 0);

	load_all_modules(0);
	load_core_modules(0);
	rehash(0);

	sendto_realops_snomask(SNO_GENERAL, L_ALL,
			     "Module Restart: %d modules unloaded, %d modules loaded",
			     modnum, num_mods);
	ilog(L_MAIN, "Module Restart: %d modules unloaded, %d modules loaded", modnum, num_mods);
	return 0;
}
