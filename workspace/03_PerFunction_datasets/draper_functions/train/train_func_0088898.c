cmd_window_goto(const char *data)
{
	WINDOW_REC *window;
	char *target;
	void *free_arg;

	g_return_if_fail(data != NULL);

	if (is_numeric(data, 0)) {
		cmd_window_refnum(data);
		return;
	}

	if (!cmd_get_params(data, &free_arg, 1, &target))
		return;

	if (g_ascii_strcasecmp(target, "active") == 0)
		window = window_highest_activity(active_win,
			settings_get_bool("active_window_ignore_refnum"));
	else {
		window = window_find_name(target);
		if (window == NULL && active_win->active_server != NULL)
			window = window_find_item_cycle(active_win->active_server, target);
		if (window == NULL)
			window = window_find_item_cycle(NULL, target);
	}

	if (window != NULL)
		window_set_active(window);

	cmd_params_free(free_arg);
}
