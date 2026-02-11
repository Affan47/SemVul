gpk_task_key_question (PkTask *task, guint request, PkResults *results)
{
	GPtrArray *array;
	GtkWidget *widget;
	gchar *printable = NULL;
	gchar *package_id = NULL;
	gchar *repository_name = NULL;
	gchar *key_url = NULL;
	gchar *key_userid = NULL;
	gchar *key_id = NULL;
	PkRepoSignatureRequired *item;
	GpkTaskPrivate *priv = GPK_TASK(task)->priv;


	priv->request = request;


	array = pk_results_get_repo_signature_required_array (results);
	if (array->len != 1) {
		g_warning ("array length %i, aborting", array->len);
		goto out;
	}


	item = g_ptr_array_index (array, 0);
	g_object_get (item,
		      "package-id", &package_id,
		      "repository-name", &repository_name,
		      "key-url", &key_url,
		      "key-userid", &key_userid,
		      "key-id", &key_id,
		      NULL);


	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder_signature, "label_name"));
	gtk_label_set_label (GTK_LABEL (widget), repository_name);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder_signature, "label_url"));
	gtk_label_set_label (GTK_LABEL (widget), key_url);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder_signature, "label_user"));
	gtk_label_set_label (GTK_LABEL (widget), key_userid);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder_signature, "label_id"));
	gtk_label_set_label (GTK_LABEL (widget), key_id);

	printable = pk_package_id_to_printable (package_id);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder_signature, "label_package"));
	gtk_label_set_label (GTK_LABEL (widget), printable);


	priv->current_window = GTK_WINDOW(gtk_builder_get_object (priv->builder_signature, "dialog_gpg"));
	if (priv->parent_window != NULL) {
		gtk_window_set_transient_for (priv->current_window, priv->parent_window);
		gtk_window_set_modal (priv->current_window, TRUE);

		gtk_window_set_title (priv->current_window, "");
	}
	priv->help_id = "gpg-signature";
	gtk_widget_show (GTK_WIDGET(priv->current_window));
out:
	g_free (printable);
	g_free (package_id);
	g_free (repository_name);
	g_free (key_url);
	g_free (key_userid);
	g_free (key_id);
	g_ptr_array_unref (array);
}
