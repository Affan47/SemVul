gtt_projects_tree_set_style (GttProjectsTree *gpt, GtkTreeStore *tree_model, GttProject *prj, GtkTreeIter *iter)
{
	GttProjectsTreePrivate *priv = GTT_PROJECTS_TREE_GET_PRIVATE (gpt);
	PangoWeight weight = PANGO_WEIGHT_NORMAL;
	gchar *bgcolor = NULL;

	if (priv->highlight_active)
	{
		if (timer_project_is_running (prj))
		{
			bgcolor = priv->active_bgcolor;
			weight = PANGO_WEIGHT_BOLD;
		}
	}
	gtk_tree_store_set (tree_model,
						iter,
						BACKGROUND_COLOR_COLUMN, bgcolor,
						WEIGHT_COLUMN, weight,
						-1);
}
