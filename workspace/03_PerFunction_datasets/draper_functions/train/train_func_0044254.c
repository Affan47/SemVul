window_remotes_row_activated_cb (GiggleRemotesView *view,
				 GtkTreePath       *path,
				 GtkTreeViewColumn *column,
				 GtkTreeView       *treeview)
{
	GiggleRemotesViewPriv *priv = GET_PRIV (view);
	GiggleRemote          *remote = NULL;
	GtkTreeModel          *model;
	GtkTreeIter            iter;
	GtkWidget             *editor;
	GtkWidget             *toplevel;
	gint                   response;

	model = gtk_tree_view_get_model (treeview);
	g_return_if_fail (gtk_tree_model_get_iter (model, &iter, path));

	gtk_tree_model_get (model, &iter,
			    COL_REMOTE, &remote,
			    -1);

	editor = giggle_remote_editor_new (remote);
	toplevel = gtk_widget_get_toplevel (GTK_WIDGET (view));
	gtk_window_set_transient_for (GTK_WINDOW (editor), GTK_WINDOW (toplevel));
	response = gtk_dialog_run (GTK_DIALOG (editor));

	if (!remote && response == GTK_RESPONSE_ACCEPT) {
		GtkListStore* store = GTK_LIST_STORE (model);
		GtkTreeIter   new;

		g_object_get (editor,
			      "remote", &remote,
			      NULL);

		gtk_list_store_insert_before (store, &new, &iter);
		gtk_list_store_set (store, &new,
				    COL_REMOTE, remote,
				    -1);
	}

	if (response == GTK_RESPONSE_ACCEPT)
		giggle_git_save_remote (priv->git, remote);

	if (remote)
		g_object_unref (remote);

	gtk_widget_destroy (editor);
}
