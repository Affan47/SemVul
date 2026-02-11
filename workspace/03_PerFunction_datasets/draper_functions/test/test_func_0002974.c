view_history_get_branches_cb (GiggleGit    *git,
			      GiggleJob    *job,
			      GError       *error,
			      gpointer      user_data)
{
	GiggleViewHistory     *view;
	GiggleViewHistoryPriv *priv;
	GiggleRevision        *revision;
	GtkTreeModel          *model;
	GtkTreePath           *path;
	GtkTreeIter            iter;
	gboolean               valid;
	GList                 *branches, *tags, *remotes;
	gboolean               changed;

	view = GIGGLE_VIEW_HISTORY (user_data);
	priv = view->priv;

	if (error) {
		GtkWidget *dialog;

		dialog = gtk_message_dialog_new (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (view))),
						 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_OK,
						 _("An error occurred when getting the revisions list:\n%s"),
						 error->message);

		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	} else {
		model = gtk_tree_view_get_model (GTK_TREE_VIEW (priv->revision_list));
		valid = gtk_tree_model_get_iter_first (model, &iter);
		branches = giggle_git_refs_get_branches (GIGGLE_GIT_REFS (job));
		tags = giggle_git_refs_get_tags (GIGGLE_GIT_REFS (job));
		remotes = giggle_git_refs_get_remotes (GIGGLE_GIT_REFS (job));

		while (valid) {
			gtk_tree_model_get (model, &iter,
					    REVISION_COL_OBJECT, &revision,
					    -1);

			if (revision) {
				changed  = view_history_add_refs (revision, branches, giggle_revision_add_branch_head);
				changed |= view_history_add_refs (revision, tags, giggle_revision_add_tag);
				changed |= view_history_add_refs (revision, remotes, giggle_revision_add_remote);

				if (changed) {
					path = gtk_tree_model_get_path (model, &iter);
					gtk_tree_model_row_changed (model, path, &iter);
					gtk_tree_path_free (path);
				}

				g_object_unref (revision);
			}

			valid = gtk_tree_model_iter_next (model, &iter);
		}
	}

	g_clear_object (&priv->job);
}
