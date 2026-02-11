hud_squadmsg_hotkey_select( int k )
{
	htarget_list *hitem, *plist;
	int send_message;
	object *objp;

	Assert ( Player->flags & PLAYER_FLAGS_MSG_MODE );

	if ( Msg_shortcut_command == -1 )
		return 0;

	Assert ( (k >= 0) && (k < MAX_KEYED_TARGETS) );
	plist = &(Player->keyed_targets[k]);

	if ( EMPTY(plist) )
		return 0;

	send_message = 1;


	for ( hitem = GET_FIRST(plist); hitem != END_OF_LIST(plist); hitem = GET_NEXT(hitem) ) {
		objp = hitem->objp;
		Assert ( objp->type == OBJ_SHIP );
		if ( Ships[objp->instance].team != Player_ship->team )
			continue;


		if ( !(Ships[objp->instance].orders_accepted & Msg_shortcut_command) )
			continue;

		hud_squadmsg_send_ship_command( objp->instance, Msg_shortcut_command, send_message, SQUADMSG_HISTORY_ADD_ENTRY );
		send_message  = 0;
	}

	hud_squadmsg_toggle();
	return 1;
}
