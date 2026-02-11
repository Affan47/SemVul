audio_profile_combo_change_cb(GtkWidget *widget, gpointer user_data)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *media_type = NULL;
	GstEncodingProfile *profile;

	model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget));

	if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (widget), &iter) == FALSE)
		return;
	gtk_tree_model_get (GTK_TREE_MODEL (model),
			    &iter,
			    0, &media_type,
			    2, &profile,
			    -1);

	rec_settings.profile = g_strdup(media_type);


	if (rb_gst_check_missing_plugins (profile, NULL, NULL)) {
		gtk_widget_set_visible (install_button, TRUE);

		gtk_widget_set_sensitive (install_button,
					gst_install_plugins_supported ());
	} else {
		gtk_widget_set_visible (install_button, FALSE);
	}
	g_free (media_type);
}
