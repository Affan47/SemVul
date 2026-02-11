brasero_project_register_ui (BraseroProject *project, GtkUIManager *manager)
{
	GError *error = NULL;
	GtkAction *action;
	GtkWidget *toolbar;


	project->priv->project_group = gtk_action_group_new ("ProjectActions1");
	gtk_action_group_set_translation_domain (project->priv->project_group, GETTEXT_PACKAGE);
	gtk_action_group_add_actions (project->priv->project_group,
				      entries,
				      G_N_ELEMENTS (entries),
				      project);

	gtk_ui_manager_insert_action_group (manager, project->priv->project_group, 0);
	if (!gtk_ui_manager_add_ui_from_string (manager,
						description,
						-1,
						&error)) {
		g_message ("building menus/toolbar failed: %s", error->message);
		g_error_free (error);
	}

	toolbar = gtk_ui_manager_get_widget (manager, "/Toolbar");
	gtk_style_context_add_class (gtk_widget_get_style_context (toolbar),
				     GTK_STYLE_CLASS_PRIMARY_TOOLBAR);

	action = gtk_action_group_get_action (project->priv->project_group, "Save");
	g_object_set (action,
		      "short-label", _("_Save"),
		      NULL);
	gtk_action_set_sensitive (action, FALSE);
	action = gtk_action_group_get_action (project->priv->project_group, "SaveAs");
	gtk_action_set_sensitive (action, FALSE);

	action = gtk_action_group_get_action (project->priv->project_group, "Burn");
	gtk_action_set_sensitive (action, FALSE);
	action = gtk_action_group_get_action (project->priv->project_group, "Add");
	gtk_action_set_sensitive (action, FALSE);
	g_object_set (action,
		      "short-label", _("_Add"),
		      NULL);
	action = gtk_action_group_get_action (project->priv->project_group, "DeleteProject");
	gtk_action_set_sensitive (action, FALSE);
	g_object_set (action,
		      "short-label", _("_Remove"),
		      NULL);
	action = gtk_action_group_get_action (project->priv->project_group, "DeleteAll");
	gtk_action_set_sensitive (action, FALSE);

	project->priv->manager = manager;

	if (gtk_widget_get_realized (project->priv->name_display))
		gtk_widget_grab_focus (project->priv->name_display);
}
