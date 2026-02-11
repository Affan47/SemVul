statusbar_config_create(STATUSBAR_GROUP_REC *group, const char *name)
{
	STATUSBAR_CONFIG_REC *bar;

        g_return_val_if_fail(group != NULL, NULL);
        g_return_val_if_fail(name != NULL, NULL);

	bar = g_new0(STATUSBAR_CONFIG_REC, 1);
	group->config_bars = g_slist_append(group->config_bars, bar);

	bar->name = g_strdup(name);
	return bar;
}
