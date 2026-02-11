statusbar_group_destroy(STATUSBAR_GROUP_REC *rec)
{
	statusbar_groups = g_slist_remove(statusbar_groups, rec);

	while (rec->bars != NULL)
		statusbar_destroy(rec->bars->data);
	while (rec->config_bars != NULL)
                statusbar_config_destroy(rec, rec->config_bars->data);

        g_free(rec->name);
        g_free(rec);
}
