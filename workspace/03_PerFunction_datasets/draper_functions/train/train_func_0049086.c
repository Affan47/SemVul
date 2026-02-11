pk_progress_set_package_id (PkProgress *progress, const gchar *package_id)
{
	g_return_val_if_fail (PK_IS_PROGRESS (progress), FALSE);


	if (g_strcmp0 (progress->priv->package_id, package_id) == 0)
		return FALSE;


	if (!pk_package_id_check (package_id)) {
		g_warning ("invalid package_id %s", package_id);
		return FALSE;
	}


	g_free (progress->priv->package_id);
	progress->priv->package_id = g_strdup (package_id);
	g_object_notify (G_OBJECT(progress), "package-id");

	return TRUE;
}
