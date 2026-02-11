ewmh_WMDesktop(EWMH_CMD_ARGS)
{
	if (ev != NULL && style == NULL)
	{

		unsigned long d = (unsigned long)ev->xclient.data.l[0];


		if (d == (unsigned long)-2 || d == (unsigned long)-1)
		{
			execute_function_override_window(
				NULL, NULL, "Stick on", 0, fw);
		}
		else if (d >= 0)
		{
			if (IS_STICKY_ACROSS_PAGES(fw) ||
			    IS_STICKY_ACROSS_DESKS(fw))
			{
				execute_function_override_window(
					NULL, NULL, "Stick off", 0, fw);
			}
			if (fw->Desk != d)
			{
				do_move_window_to_desk(fw, (int)d);
			}
		}
		else
		{
			fvwm_msg(
				WARN, "ewmh_WMDesktop",
				"The application window (id %#lx)\n"
				"  \"%s\" tried to move to an invalid desk"
				" (%ld)\n"
				"  using an EWMH client message.\n"
				"    fvwm is ignoring this request.\n",
				fw ? FW_W(fw) : 0,
				fw ? fw->name.name : "(none)",
				ev->xclient.data.l[0]);
			fvwm_msg_report_app_and_workers();
		}

		return 0;
	}

	if (style != NULL && ev == NULL)
	{

		CARD32 *val;
		int size = 0;

		if (DO_EWMH_IGNORE_STATE_HINTS(style))
		{
			SET_HAS_EWMH_INIT_WM_DESKTOP(
				fw, EWMH_STATE_UNDEFINED_HINT);

			return 0;
		}
		if (HAS_EWMH_INIT_WM_DESKTOP(fw) != EWMH_STATE_UNDEFINED_HINT)
		{
			return 0;
		}
		val = ewmh_AtomGetByName(
			FW_W(fw), "_NET_WM_DESKTOP", EWMH_ATOM_LIST_CLIENT_WIN,
			&size);
		if (val == NULL)
		{
			SET_HAS_EWMH_INIT_WM_DESKTOP(fw, EWMH_STATE_NO_HINT);

			return 0;
		}
#if DEBUG_EWMH_INIT_STATE
		fprintf(
			stderr, "ewmh WM_DESKTOP hint for window 0x%lx  "
			"(%i,%lu,%u)\n", FW_W(fw),
			HAS_EWMH_INIT_WM_DESKTOP(fw),
			fw->ewmh_hint_desktop, val[0]);
#endif
		if (val[0] == (CARD32)-2 || val[0] == (CARD32)-1)
		{
			S_SET_IS_STICKY_ACROSS_PAGES(SCF(*style), 1);
			S_SET_IS_STICKY_ACROSS_PAGES(SCM(*style), 1);
			S_SET_IS_STICKY_ACROSS_PAGES(SCC(*style), 1);
			S_SET_IS_STICKY_ACROSS_DESKS(SCF(*style), 1);
			S_SET_IS_STICKY_ACROSS_DESKS(SCM(*style), 1);
			S_SET_IS_STICKY_ACROSS_DESKS(SCC(*style), 1);
		}
		else if (val[0] < 256)
		{

			style->flags.use_start_on_desk = 1;
			style->flag_mask.use_start_on_desk = 1;
			style->change_mask.use_start_on_desk = 1;
			SSET_START_DESK(*style, val[0]);
		}
		SET_HAS_EWMH_INIT_WM_DESKTOP(fw, EWMH_STATE_HAS_HINT);
		fw->ewmh_hint_desktop = val[0];
		free(val);
	}
	return 0;
}
