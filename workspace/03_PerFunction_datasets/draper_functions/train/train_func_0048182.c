do_cmd_store(cmd_code code, cmd_arg args[])
{

	struct store *store = current_store();
	menu_type menu;


	if (!store) {
		msg("You see no store here.");
		return;
	}


	if (OPT(birth_no_stores)) {
		msg("The doors are locked.");
		return;
	}


	event_signal(EVENT_LEAVE_GAME);
	event_signal(EVENT_ENTER_STORE);


	forget_view();


	p_ptr->command_arg = 0;


	screen_save();


	menu_init(&menu, MN_SKIN_SCROLL, &store_menu);
	menu_layout(&menu, &store_menu_region);

	store_menu_set_selections(&menu, FALSE);
	store_flags = STORE_INIT_CHANGE;
	store_display_recalc(&menu);
	store_menu_recalc(&menu);
	store_redraw();


	if (store->sidx != STORE_HOME)
		prt_welcome(store->owner);

	msg_flag = FALSE;
	menu_select(&menu, 0, FALSE);
	msg_flag = FALSE;


	event_signal(EVENT_LEAVE_STORE);
	event_signal(EVENT_ENTER_GAME);


	p_ptr->energy_use = 100;


	message_flush();


	screen_load();


	p_ptr->update |= (PU_UPDATE_VIEW | PU_MONSTERS);


	p_ptr->redraw |= (PR_BASIC | PR_EXTRA);


	p_ptr->redraw |= (PR_MAP);
}
