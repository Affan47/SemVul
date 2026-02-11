glade_app_remove_project (GladeProject *project)
{
	GladeApp *app;
	g_return_if_fail (GLADE_IS_PROJECT (project));

	app = glade_app_get ();

	app->priv->projects = g_list_remove (app->priv->projects, project);


	app->priv->active_project = NULL;


	if (app->priv->projects == NULL)
	{

		gtk_widget_set_sensitive (GTK_WIDGET (app->priv->palette), FALSE);


		glade_editor_load_widget (app->priv->editor, NULL);
		gtk_widget_set_sensitive (GTK_WIDGET (app->priv->editor), FALSE);
	}
	else
		glade_app_set_project (g_list_last (app->priv->projects)->data);


	g_object_unref (project);
}
