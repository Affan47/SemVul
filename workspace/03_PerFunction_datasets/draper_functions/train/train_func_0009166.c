brasero_project_name_set_session (BraseroProjectName *project,
				  BraseroBurnSession *session)
{
	BraseroProjectNamePrivate *priv;

	priv = BRASERO_PROJECT_NAME_PRIVATE (project);

	brasero_project_name_unset_session (project);
	if (!session)
		return;

	priv->session = g_object_ref (session);

	g_signal_connect (priv->session,
			  "track-added",
			  G_CALLBACK (brasero_project_name_track_added),
			  project);
	g_signal_connect (priv->session,
			  "track-changed",
			  G_CALLBACK (brasero_project_name_track_changed),
			  project);
	g_signal_connect (priv->session,
			  "track-removed",
			  G_CALLBACK (brasero_project_name_track_removed),
			  project);
	g_signal_connect (priv->session,
			  "notify::flags",
			  G_CALLBACK (brasero_project_name_flags_changed),
			  project);

	brasero_project_name_session_changed (project);
}
