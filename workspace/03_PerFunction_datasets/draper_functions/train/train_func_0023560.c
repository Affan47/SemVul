display_value (GttIdleDialog *dlg, time_t credit)
{
	char tbuff [30];
	char mbuff [130];
	char * msg;
	time_t now = time(0);
	time_t idle_time;


	if (3600 > credit)
	{
		xxxqof_print_minutes_elapsed_buff (tbuff, 30, credit, TRUE);
		g_snprintf (mbuff, 130, _("%s minutes"), tbuff);
	}
	else
	{
		xxxqof_print_hours_elapsed_buff (tbuff, 30, credit, FALSE);
		g_snprintf (mbuff, 130, _("%s hours"), tbuff);
	}
	gtk_label_set_text (dlg->time_label, mbuff);


	if (3600 > credit)
	{
		msg = g_strdup_printf (
		         _("The timer will be credited "
		           "with %ld minutes since the last keyboard/mouse "
		           "activity.  If you want to change the amount "
		           "of time credited, use the slider below to "
		           "adjust the value."),
		           (credit+30)/60);
	}
	else
	{
		msg = g_strdup_printf (
		         _("The timer will be credited "
		           "with %s hours since the last keyboard/mouse "
		           "activity.  If you want to change the amount "
		           "of time credited, use the slider below to "
		           "adjust the value."),
		           tbuff);
	}
	gtk_label_set_text (dlg->credit_label, msg);
	g_free (msg);


	idle_time = now - dlg->last_activity;

	char *ptitle = util_escape_html_markup (
	                            gtt_project_get_title(dlg->prj));
	char *pdesc = util_escape_html_markup (
	                            gtt_project_get_desc(dlg->prj));
	if (3600 > idle_time)
	{
		msg = g_strdup_printf (
			_("The keyboard and mouse have been idle "
			  "for %ld minutes.  The currently running "
			  "project, <b><i>%s - %s</i></b>, "
			  "has been stopped. "
			  "Do you want to restart it?"),
			(idle_time+30)/60, ptitle, pdesc);
	}
	else
	{
		msg = g_strdup_printf (
			_("The keyboard and mouse have been idle "
			  "for %ld:%02ld hours.  The currently running "
			  "project (%s - %s) "
			  "has been stopped. "
			  "Do you want to restart it?"),
			(idle_time+30)/3600, ((idle_time+30)/60)%60,
		   ptitle, pdesc);
	}

	gtk_label_set_markup (dlg->idle_label, msg);
	g_free (msg);
	g_free (ptitle);
	g_free (pdesc);
}
