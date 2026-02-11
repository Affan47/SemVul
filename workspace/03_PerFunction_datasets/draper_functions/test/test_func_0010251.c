gpk_helper_run_add_desktop_file (GpkHelperRun *helper, const gchar *package_id, const gchar *filename)
{
	gboolean ret = FALSE;
	gchar *icon = NULL;
	gchar *text = NULL;
	gchar *fulltext = NULL;
	gchar *name = NULL;
	gchar *exec = NULL;
	gchar *summary = NULL;
	gchar *joint = NULL;
	GtkTreeIter iter;
	GKeyFile *file = NULL;
	gint weight;
	gboolean hidden;


	weight = gpk_desktop_get_file_weight (filename);
	if (weight < 0) {
		g_debug ("ignoring %s", filename);
		goto out;
	}


	file = g_key_file_new ();
	ret = g_key_file_load_from_file (file, filename, G_KEY_FILE_NONE, NULL);
	if (!ret) {
		g_debug ("failed to load %s", filename);
		goto out;
	}


	hidden = g_key_file_get_boolean (file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_HIDDEN, NULL);
	if (hidden) {
		g_debug ("hidden, so ignoring %s", filename);
		ret = FALSE;
		goto out;
	}


	ret = !g_key_file_has_group (file, "Window Manager");
	if (!ret) {
		g_debug ("ignoring Window Manager");
		goto out;
	}


	exec = g_key_file_get_string (file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_TRY_EXEC, NULL);
	if (exec == NULL)
		exec = g_key_file_get_string (file, G_KEY_FILE_DESKTOP_GROUP, "Exec", NULL);


	if (exec == NULL) {
		ret = FALSE;
		goto out;
	}


	text = g_key_file_get_locale_string (file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL, NULL);
	if (text != NULL)
		name = g_markup_escape_text (text, -1);


	icon = g_key_file_get_string (file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, NULL);
	if (icon == NULL || !gpk_desktop_check_icon_valid (icon)) {
		g_free (icon);
		icon = g_strdup (gpk_info_enum_to_icon_name (PK_INFO_ENUM_AVAILABLE));
	}


	summary = g_key_file_get_locale_string (file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_COMMENT, NULL, NULL);
	if (summary == NULL)
		summary = g_key_file_get_locale_string (file, G_KEY_FILE_DESKTOP_GROUP, "GenericName", NULL, NULL);


	gtk_list_store_append (helper->priv->list_store, &iter);
	joint = g_strdup_printf ("%s - %s", name, summary);
	fulltext = gpk_package_id_format_twoline (NULL, package_id, joint);

	gtk_list_store_set (helper->priv->list_store, &iter,
			    GPK_CHOOSER_COLUMN_TEXT, fulltext,
			    GPK_CHOOSER_COLUMN_FILENAME, filename,
			    GPK_CHOOSER_COLUMN_ICON, icon, -1);
out:
	if (file != NULL)
		g_key_file_free (file);
	g_free (exec);
	g_free (icon);
	g_free (name);
	g_free (text);
	g_free (joint);
	g_free (summary);

	return ret;
}
