gtt_project_compat_set_secs (GttProject *proj, int sever, int sday, time_t last)
{
	time_t midnight;
	GttTask *tsk;
	GttInterval *ivl;


	midnight = get_midnight (last);


	tsk = gtt_task_new ();
	gtt_task_set_memo (tsk, _("Old GTT Tasks"));

	ivl = gtt_interval_new();
	ivl->stop = midnight - 1;
	ivl->start = midnight - 1 - sever + sday;
	gtt_task_add_interval (tsk, ivl);

	if (0 < sday)
	{
		ivl = gtt_interval_new();
		ivl->start = midnight +1;
		ivl->stop = midnight + sday + 1;
		gtt_task_add_interval (tsk, ivl);
	}

	gtt_project_append_task (proj, tsk);


	tsk = gtt_task_new ();
	gtt_task_set_memo (tsk, _("New Diary Entry"));
	gtt_project_append_task (proj, tsk);

	proj_refresh_time (proj);
}
