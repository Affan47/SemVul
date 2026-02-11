gkm_gnome2_storage_new (GkmModule *module, const gchar *directory)
{
	GkmManager *manager;

	g_return_val_if_fail (GKM_IS_MODULE (module), NULL);
	g_return_val_if_fail (directory, NULL);

	manager = gkm_module_get_manager (module);
	g_return_val_if_fail (GKM_IS_MANAGER (manager), NULL);

	return g_object_new (GKM_TYPE_GNOME2_STORAGE,
	                     "module", module,
	                     "manager", manager,
	                     "directory", directory,
	                     NULL);
}
