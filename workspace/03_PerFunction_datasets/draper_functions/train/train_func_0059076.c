brasero_project_set_none (BraseroProject *project)
{
	GtkAction *action;
	GtkWidget *status;

	brasero_project_reset (project);


	action = gtk_action_group_get_action (project->priv->project_group, "Add");
	gtk_action_set_visible (action, FALSE);
	action = gtk_action_group_get_action (project->priv->project_group, "DeleteProject");
	gtk_action_set_visible (action, FALSE);
	action = gtk_action_group_get_action (project->priv->project_group, "DeleteAll");
	gtk_action_set_visible (action, FALSE);
	action = gtk_action_group_get_action (project->priv->project_group, "SaveAs");
	gtk_action_set_sensitive (action, FALSE);
	action = gtk_action_group_get_action (project->priv->project_group, "Save");
	gtk_action_set_sensitive (action, FALSE);

	if (project->priv->merge_id)
		gtk_ui_manager_remove_ui (project->priv->manager,
					  project->priv->merge_id);

	status = brasero_app_get_statusbar2 (brasero_app_get_default ());

	if (project->priv->status_ctx)
		gtk_statusbar_pop (GTK_STATUSBAR (status), project->priv->status_ctx);
}
