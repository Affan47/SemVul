show_idle_dialog (GttIdleDialog *id)
{
	time_t now;
	time_t idle_time;
	GttProject *prj = cur_proj;

	if (!id) return;
	if (0 > config_idle_timeout) return;
	if (!prj) return;

	now = time(0);
	idle_time = now - id->last_activity;


	if (NULL == id->gtxml)
	{
		idle_dialog_realize (id);
	}


	id->visible = TRUE;


	cur_proj_set (NULL);

	id->prj = prj;


	id->previous_credit = idle_time;
	adjust_timer (id, config_idle_timeout);


	raise_idle_dialog (id);

}
