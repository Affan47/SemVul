gitg_revision_panel_get_panel_impl (GitgRevisionPanel *panel)
{
	GtkBuilder *builder;
	GtkWidget *ret;
	GitgRevisionChangesPanel *changes_panel;

	changes_panel = GITG_REVISION_CHANGES_PANEL (panel);

	if (changes_panel->priv->panel_widget)
	{
		return changes_panel->priv->panel_widget;
	}

	builder = gitg_utils_new_builder ("gitg-revision-changes-panel.ui");
	changes_panel->priv->builder = builder;

	ret = GTK_WIDGET (gtk_builder_get_object (builder, "revision_changes_page"));
	changes_panel->priv->panel_widget = ret;

	initialize_ui (changes_panel);

	return ret;
}
