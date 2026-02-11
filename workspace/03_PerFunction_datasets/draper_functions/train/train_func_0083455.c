brasero_app_process_session (BraseroApp *app,
			     BraseroSessionCfg *session,
			     gboolean burn)
{
	if (!burn) {
		GtkWidget *manager;
		BraseroAppPrivate *priv;

		priv = BRASERO_APP_PRIVATE (app);
		if (!priv->mainwin)
			brasero_app_create_mainwin (app);

		manager = brasero_app_get_project_manager (app);
		brasero_project_manager_open_session (BRASERO_PROJECT_MANAGER (manager), session);
	}
	else
		brasero_app_session_burn (app, session, TRUE);
}
