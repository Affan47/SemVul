e2_filelist_enable_refresh (void)
{
	refresh_refcount--;
#ifdef E2_REFRESH_DEBUG
	printd (DEBUG, "enable refresh, refresh ref now = %d", refresh_refcount);
#endif
	if (refresh_refcount < 0)
	{
		printd (WARN, "The auto-refresh refresh count is < 0");
		gdk_threads_enter ();
		e2_window_output_show (NULL, NULL);
		e2_output_print_error (
		_("Something is wrong with the auto-refresh mechanism"), FALSE);
		gdk_threads_leave ();
	}

	if (refresh_refcount == 0)
	{
		if (e2_option_bool_get ("auto-refresh"))
		{
			LISTS_LOCK
			curr_view->listcontrols.norefresh = FALSE;
			other_view->listcontrols.norefresh = FALSE;
			LISTS_UNLOCK
		}

		if (e2_option_bool_get ("auto-refresh-config"))
			app.timers[CONFIG_T] =
#ifdef USE_GLIB2_14
			g_timeout_add_seconds (E2_CONFIGCHECK_INTERVAL_S,
#else
			g_timeout_add (E2_CONFIGCHECK_INTERVAL,
#endif
				(GSourceFunc) e2_option_check_config_files, NULL);

#ifndef E2_STATUS_DEMAND
		e2_window_enable_status_update (-1);
#endif
	}
}
