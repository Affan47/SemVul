cmd_window_down(void)
{
	MAIN_WINDOW_REC *rec;

	rec = mainwindows_find_lower(active_mainwin->last_line);
	if (rec == NULL)
		rec = mainwindows_find_lower(-1);
	if (rec != NULL)
		window_set_active(rec->active);
}
