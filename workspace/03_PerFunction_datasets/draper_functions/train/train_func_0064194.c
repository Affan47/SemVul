_gconf_cleaner_run_cleaning_cb(gpointer data)
{
	GConfCleanerInstance *inst = data;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gboolean flag;
	gchar *key;
	guint i = 0;
	GtkWidget *page;
	GError *error = NULL;

	if (inst->n_unknown_pairs == 0)
		goto next;
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR (inst->progressbar2),
					 GTK_PROGRESS_LEFT_TO_RIGHT);
	gtk_progress_bar_set_ellipsize(GTK_PROGRESS_BAR (inst->progressbar2),
				       PANGO_ELLIPSIZE_MIDDLE);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR (inst->progressbar2), 0.0);

	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL, TRUE);

	model = gtk_tree_view_get_model(GTK_TREE_VIEW (inst->treeview));
	if (G_LIKELY (gtk_tree_model_get_iter_first(model, &iter))) {
		do {
			gtk_tree_model_get(model, &iter, 0, &flag, 1, &key, -1);
			if (flag) {
				i++;
				gtk_progress_bar_set_text(GTK_PROGRESS_BAR (inst->progressbar2), key);
				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR (inst->progressbar2),
							      (gdouble)i / (gdouble)inst->n_unknown_pairs);

				while (g_main_context_pending(NULL))
					g_main_context_iteration(NULL, TRUE);

				gconf_cleaner_unset_key(inst->cleaner, key, &error);
				if (G_UNLIKELY (error)) {
					_gconf_cleaner_error_dialog(inst,
								    _("<span weight=\"bold\" size=\"larger\">Failed during cleaning GConf key up.</span>"),
								    error->message,
								    TRUE);
					return FALSE;
				}
			}
			g_free(key);
		} while (gtk_tree_model_iter_next(model, &iter));
		gconf_cleaner_sync(inst->cleaner, &error);
	}
  next:
	page = gtk_assistant_get_nth_page(GTK_ASSISTANT (inst->window),
					  gtk_assistant_get_current_page(GTK_ASSISTANT (inst->window)));
	gtk_assistant_set_page_complete(GTK_ASSISTANT (inst->window),
					page, TRUE);
	gtk_widget_set_sensitive(GTK_ASSISTANT (inst->window)->back, FALSE);
	g_signal_emit_by_name(GTK_ASSISTANT (inst->window)->forward, "clicked");

	return FALSE;
}
