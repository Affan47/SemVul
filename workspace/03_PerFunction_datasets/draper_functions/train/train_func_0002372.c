cb_general(void)
	{
#if !defined(WIN32)
	gint		n;
	gboolean	new_state;
#endif

	if (allow_multiple_button)
		_GK.allow_multiple_instances =
					GTK_TOGGLE_BUTTON(allow_multiple_button)->active;
	if (on_top_button)
		_GK.on_top = GTK_TOGGLE_BUTTON(on_top_button)->active;

	_GK.save_position = GTK_TOGGLE_BUTTON(save_position_button)->active;
#if !defined(WIN32)
	if (sticky_state_button)
		{
		n = GTK_TOGGLE_BUTTON(sticky_state_button)->active;
		new_state = (n != _GK.sticky_state);
		_GK.sticky_state = n;
		if (new_state)
			{
			GtkWidget	*top_window = gkrellm_get_top_window();

			if (_GK.sticky_state)
				gtk_window_stick(GTK_WINDOW(top_window));
			else
				gtk_window_unstick(GTK_WINDOW(top_window));
			}
		}

	if (decorated_button)
		_GK.decorated = GTK_TOGGLE_BUTTON(decorated_button)->active;

	if (skip_taskbar_button)
		{
		n = GTK_TOGGLE_BUTTON(skip_taskbar_button)->active;
		new_state = (n != _GK.state_skip_taskbar);
		_GK.state_skip_taskbar = n;
		if (new_state)
			gkrellm_winop_state_skip_taskbar(n);
		}
	if (skip_pager_button)
		{
		n = GTK_TOGGLE_BUTTON(skip_pager_button)->active;
		new_state = (n != _GK.state_skip_pager);
		_GK.state_skip_pager = n;
		if (new_state)
			gkrellm_winop_state_skip_pager(n);
		}
	if (above_button)
		{
		n = GTK_TOGGLE_BUTTON(above_button)->active;
		new_state = (n != _GK.state_above);
		_GK.state_above = n;
		if (new_state)
			{
			if (n && _GK.state_below)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(below_button),
						FALSE);
			gkrellm_winop_state_above(n);
			}
		}
	if (below_button)
		{
		n = GTK_TOGGLE_BUTTON(below_button)->active;
		new_state = (n != _GK.state_below);
		_GK.state_below = n;
		if (new_state)
			{
			if (n && _GK.state_above)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(above_button),
						FALSE);
			gkrellm_winop_state_below(n);
			}
		}
#endif
	}
