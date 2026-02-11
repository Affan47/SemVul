cmc_config_registered_foreach(void (*func)(CmdCfg *cmc, gpointer user), gpointer user)
{
	const GList	*iter;

	for(iter = cmdcfg_list; iter != NULL; iter = g_list_next(iter))
		func(iter->data, user);
}
