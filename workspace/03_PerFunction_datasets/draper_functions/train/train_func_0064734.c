up_dock_refresh (UpDock *dock)
{
	GList *devices;
	GList *l;
	GUdevDevice *native;
	guint count = 0;


	devices = g_udev_client_query_by_subsystem (dock->priv->gudev_client,
						    "drm");
	for (l = devices; l != NULL; l = l->next) {
		native = l->data;
		count += up_dock_device_check (native);
	}
	g_list_foreach (devices, (GFunc) g_object_unref, NULL);
	g_list_free (devices);


	up_daemon_set_is_docked (dock->priv->daemon, (count > 1));

	return TRUE;
}
