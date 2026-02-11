revision_view_update (GiggleRevisionView *view)
{
	GiggleRevisionViewPriv *priv;
	GtkTextBuffer          *buffer;
	const char             *sha = NULL;
	GiggleAuthor           *author = NULL;
	GiggleAuthor           *committer = NULL;
	char                    str[256];
	const struct tm        *date;

	priv = GET_PRIV (view);

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (priv->log));
	gtk_text_buffer_set_text (buffer, "", -1);

	if (priv->revision) {
		sha       = giggle_revision_get_sha       (priv->revision);
		date      = giggle_revision_get_date      (priv->revision);
		author    = giggle_revision_get_author    (priv->revision);
		committer = giggle_revision_get_committer (priv->revision);

		if (date) {
			strftime (str, sizeof (str), "%c", date);
			gtk_label_set_text (GTK_LABEL (priv->date), str);
		} else {
			gtk_label_set_text (GTK_LABEL (priv->date), NULL);
		}

		if (priv->job) {
			giggle_git_cancel_job (priv->git, priv->job);
			g_object_unref (priv->job);
		}

		priv->job = giggle_git_log_new (priv->revision);

		giggle_git_run_job (priv->git, priv->job,
				    revision_view_update_log_cb, view);
	} else {
		gtk_label_set_text (GTK_LABEL (priv->date), NULL);
	}

	update_autor_button (priv->author, priv->avatar, author);
	update_autor_button (priv->committer, NULL, committer);
	gtk_label_set_text (GTK_LABEL (priv->sha), sha);
	revision_view_update_branches_label (view);

	if (priv->revision) {
		gtk_widget_show (priv->grid);
	} else {
		gtk_widget_hide (priv->grid);
	}
}
