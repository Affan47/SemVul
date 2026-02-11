resource_default_toggled (GtkWidget *widget,
			  GladeProject *project)
{
	if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		return;

	glade_project_set_resource_path (project, NULL);
	gtk_widget_set_sensitive (project->priv->relative_path_entry, FALSE);
	gtk_widget_set_sensitive (project->priv->full_path_button, FALSE);
}
