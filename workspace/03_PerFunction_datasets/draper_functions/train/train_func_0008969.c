update_project_completion (GladeProject    *project,
                           GladeWidget     *widget,
                           GladeInspector  *inspector)
{
	GladeInspectorPrivate *priv = inspector->priv;
	const GList* items;

	g_completion_clear_items (priv->completion);

	if (!priv->project)
		return;

	items = glade_project_get_objects (priv->project);


	g_completion_add_items (priv->completion, (GList *)items);
}
