gpk_application_remove (GpkApplicationPrivate *priv)
{
	gboolean ret;
	gchar *package_id_selected = NULL;
	gchar *summary_selected = NULL;
	PkPackage *package;


	ret = gpk_application_get_selected_package (priv, &package_id_selected, &summary_selected);
	if (!ret) {
		g_warning ("no package selected");
		goto out;
	}


	if (priv->action == GPK_ACTION_INSTALL) {
		ret = pk_package_sack_remove_package_by_id (priv->package_sack, package_id_selected);
		if (ret) {
			g_debug ("removed %s from package array", package_id_selected);


			gpk_application_allow_install (priv, TRUE);
			gpk_application_allow_remove (priv, FALSE);
			gpk_application_packages_checkbox_invert (priv);
			ret = TRUE;
			goto out;
		}
		g_warning ("wrong mode and not in array");
		ret = FALSE;
		goto out;
	}


	ret = (pk_package_sack_find_by_id (priv->package_sack, package_id_selected) == NULL);
	if (!ret) {
		g_warning ("already added");
		goto out;
	}

	priv->action = GPK_ACTION_REMOVE;
	package = pk_package_new ();
	pk_package_set_id (package, package_id_selected, NULL);
	g_object_set (package,
		      "info", PK_INFO_ENUM_INSTALLED,
		      "summary", summary_selected,
		      NULL);
	pk_package_sack_add_package (priv->package_sack, package);
	g_object_unref (package);


	gpk_application_allow_install (priv, TRUE);
	gpk_application_allow_remove (priv, FALSE);
	gpk_application_packages_checkbox_invert (priv);
out:

	gpk_application_change_queue_status (priv);
	g_free (package_id_selected);
	g_free (summary_selected);
	return TRUE;
}
