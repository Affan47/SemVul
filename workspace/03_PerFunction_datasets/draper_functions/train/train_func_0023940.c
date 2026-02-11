command_module_destroy(COMMAND_REC *rec,
				   COMMAND_MODULE_REC *modrec)
{
	GSList *tmp, *freelist;

        command_module_free(modrec, rec);


        freelist = NULL;
	for (tmp = rec->modules; tmp != NULL; tmp = tmp->next) {
		COMMAND_MODULE_REC *rec = tmp->data;

		if (rec->callbacks == NULL)
			freelist = g_slist_append(freelist, rec);
		else {
                        g_slist_free(freelist);
                        freelist = NULL;
			break;
		}
	}

	g_slist_foreach(freelist, (GFunc) command_module_free, rec);
	g_slist_free(freelist);

	if (rec->modules == NULL)
		command_free(rec);
}
