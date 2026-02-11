service_delete(service_t *sptr)
{
	struct ConfTable *subblock;

	mowgli_patricia_delete(services_name, sptr->internal_name);
	mowgli_patricia_delete(services_nick, sptr->nick);

	if (sptr->conf_table != NULL)
	{
		del_conf_item("ALIASES", sptr->conf_table);
		del_conf_item("REAL", sptr->conf_table);
		del_conf_item("HOST", sptr->conf_table);
		del_conf_item("USER", sptr->conf_table);
		del_conf_item("NICK", sptr->conf_table);
		subblock = find_top_conf(sptr->internal_name);
		if (subblock != NULL && conftable_get_conf_handler(subblock) == conf_service)
			del_top_conf(sptr->internal_name);
	}

	if (sptr->me != NULL)
	{
		quit_sts(sptr->me, "Service unloaded.");
		user_delete(sptr->me, "Service unloaded.");
		sptr->me = NULL;
	}
	sptr->handler = NULL;
	if (sptr->aliases)
		mowgli_patricia_destroy(sptr->aliases, free_alias_string, NULL);
	if (sptr->commands)
		mowgli_patricia_destroy(sptr->commands, NULL, NULL);
	free(sptr->disp);
	free(sptr->internal_name);
	free(sptr->nick);
	free(sptr->user);
	free(sptr->host);
	free(sptr->real);

	mowgli_heap_free(service_heap, sptr);
}
