_SetFocusWindow(
	FvwmWindow *fw, Bool do_allow_force_broadcast,
	fpol_set_focus_by_t set_by, Bool client_entered)
{
	sftfwin_args_t sf_args;

	memset(&sf_args, 0, sizeof(sf_args));
	sf_args.do_allow_force_broadcast = !!do_allow_force_broadcast;
	sf_args.is_focus_by_flip_focus_cmd = 0;
	sf_args.do_forbid_warp = 0;
	sf_args.do_force = 1;
	sf_args.set_by = set_by;
        if (client_entered)
	{
		sf_args.client_entered = 1;
	}
	else
	{
		sf_args.client_entered = 0;
	}
	set_focus_to_fwin(FW_W(fw), fw, &sf_args);

	return;
}
