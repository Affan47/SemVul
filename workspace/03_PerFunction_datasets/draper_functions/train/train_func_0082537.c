xkl_engine_process_focus_out_evt(XklEngine * engine,
				 XFocusChangeEvent * fev)
{
	if (!
	    (xkl_engine_is_listening_for
	     (engine, XKLL_MANAGE_WINDOW_STATES)))
		return;

	if (fev->mode != NotifyNormal) {
		xkl_debug(200,
			  "Window " WINID_FORMAT
			  " has lost focus during special action %d\n",
			  fev->window, fev->mode);
		return;
	}

	xkl_debug(160, "Window " WINID_FORMAT ", '%s' has lost focus\n",
		  fev->window, xkl_get_debug_window_title(engine,
							  fev->window));

	if (xkl_engine_is_toplevel_window_transparent(engine, fev->window)) {
		xkl_debug(150, "Leaving transparent window!\n");


		xkl_engine_priv(engine, skip_one_restore) = TRUE;
	} else {
		Window p;
		if (xkl_engine_find_toplevel_window
		    (engine, fev->window, &p))
			xkl_engine_priv(engine, prev_toplvl_win) = p;
	}
}
