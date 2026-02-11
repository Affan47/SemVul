CloseGeneralPluginManager(PILPlugin* us)
{

	GHashTable*	MasterTable = us->ud_plugin;
	int		count;

	g_assert(MasterTable != NULL);


	if ((count=g_hash_table_size(MasterTable)) > 0) {


		g_hash_table_foreach_remove(MasterTable, FreeAKey, NULL);
	}
	g_hash_table_destroy(MasterTable);
	us->ud_plugin = NULL;
	return;
}
