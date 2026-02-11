brasero_project_update_project_size (BraseroProject *project)
{
	BraseroTrackType *session_type;
	goffset sectors = 0;
	GtkWidget *status;
	gchar *size_str;
	gchar *string;

	status = brasero_app_get_statusbar2 (brasero_app_get_default ());

	if (!project->priv->status_ctx)
		project->priv->status_ctx = gtk_statusbar_get_context_id (GTK_STATUSBAR (status),
									  "size_project");

	gtk_statusbar_pop (GTK_STATUSBAR (status), project->priv->status_ctx);

	brasero_burn_session_get_size (BRASERO_BURN_SESSION (project->priv->session),
				       &sectors,
				       NULL);

	session_type = brasero_track_type_new ();
	brasero_burn_session_get_input_type (BRASERO_BURN_SESSION (project->priv->session), session_type);

	string = brasero_project_get_sectors_string (sectors, session_type);
	brasero_track_type_free (session_type);

	size_str = g_strdup_printf (_("Estimated project size: %s"), string);
	g_free (string);

	gtk_statusbar_push (GTK_STATUSBAR (status), project->priv->status_ctx, size_str);
	g_free (size_str);
}
