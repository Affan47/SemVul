glade_design_view_set_project (GladeDesignView *view, GladeProject *project)
{
	g_return_if_fail (GLADE_IS_PROJECT (project));

	view->priv->project = project;

	g_signal_connect (project, "parse-began", G_CALLBACK (glade_design_view_parse_began), view);
	g_signal_connect (project, "parse-finished", G_CALLBACK (glade_design_view_parse_finished), view);
	g_signal_connect (project, "load-progress", G_CALLBACK (glade_design_view_load_progress), view);

	g_object_set_data (G_OBJECT (view->priv->project), GLADE_DESIGN_VIEW_KEY, view);
}
