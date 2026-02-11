edit_task_ui(GtkWidget *w, gpointer data)
{
	GttProject *prj;
	GttTask *task;

	prj = gtt_projects_tree_get_selected_project (projects_tree);
	if (!prj) return;

	task = gtt_project_get_first_task(prj);
	prop_task_dialog_show (task);
}
