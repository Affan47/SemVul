glade_project_selection_set (GladeProject *project,
			     GObject      *object,
			     gboolean      emit_signal)
{
	g_return_if_fail (GLADE_IS_PROJECT (project));
	g_return_if_fail (G_IS_OBJECT      (object));
	g_return_if_fail (glade_project_has_object (project, object));

	if (project->priv->selection == NULL)
		glade_project_set_has_selection (project, TRUE);

	if (glade_project_is_selected (project, object) == FALSE ||
	    g_list_length (project->priv->selection) != 1)
	{
		glade_project_selection_clear (project, FALSE);
		glade_project_selection_add (project, object, emit_signal);
	}
}
