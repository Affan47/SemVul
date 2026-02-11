set_timer_button_state(gint decal_state)
	{
	timer_button_old_state = timer_button_state;
	timer_button_state = decal_state;
	gkrellm_draw_decal_pixmap(timer_panel, button_decal, decal_state);
	gkrellm_draw_panel_layers(timer_panel);

	if (   (_GK.debug_level & DEBUG_TIMER)
		&& timer_button_state != timer_button_old_state
	   )
		g_print(_("set_timer_button_state from %d to %d (check=%d)\n"),
			timer_button_old_state, timer_button_state, check_connect_state);
	}
