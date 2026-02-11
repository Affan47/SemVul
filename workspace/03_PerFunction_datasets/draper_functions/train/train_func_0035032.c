gtt_project_prepend_task (GttProject *proj, GttTask *task)
{
	int is_running = FALSE;
	if (!proj || !task) return;


	if (task->parent)
	{
		task->parent->task_list =
			g_list_remove (task->parent->task_list, task);
		proj_refresh_time(task->parent);
	}


	if (proj->task_list)
	{
		GttTask *leadtask = proj->task_list->data;
		is_running = task_suspend (leadtask);
	}

	proj->task_list = g_list_prepend (proj->task_list, task);
	task->parent = proj;

	if (is_running) gtt_project_timer_start (proj);
	proj_refresh_time(proj);
}
