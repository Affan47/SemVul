hud_squadmsg_repair_rearm( int toggle_state, object *objp)
{
	int robjnum;
	object *robjp;
	object *tobj;
	int multi_player_num;
	int multi_player_team;


	if(objp == NULL) {
		tobj = Player_obj;
		multi_player_num = -1;
		multi_player_team = -1;
	} else {
		tobj = objp;
		multi_player_num = multi_find_player_by_object(objp);
		Assert(multi_player_num != -1);
		if (multi_player_num != -1) {
			multi_player_team = Net_players[multi_player_num].p_info.team;
		}
		else {
			multi_player_team = -1;
		}
	}


	if ( is_support_allowed(tobj) ) {
		if ( mission_is_repair_scheduled( tobj ) ) {
			message_send_builtin_to_player( MESSAGE_REARM_ON_WAY, NULL, MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, multi_player_team );
		} else {
			robjnum = hud_support_find_closest(OBJ_INDEX(tobj));
			if ( robjnum != -1 ) {
				message_send_builtin_to_player( MESSAGE_REARM_ON_WAY, &Ships[Objects[robjnum].instance], MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, multi_player_team );
			} else {

				robjnum = ai_issue_rearm_request( tobj );
				if ( robjnum != -1) {
					robjp = &Objects[robjnum];
					message_send_builtin_to_player( MESSAGE_ON_WAY, &Ships[robjp->instance], MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, multi_player_team );

				} else {


					message_send_builtin_to_player( MESSAGE_REARM_WARP, NULL, MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, multi_player_team );
				}

				mission_log_add_entry(LOG_PLAYER_CALLED_FOR_REARM, Ships[tobj->instance].ship_name, NULL);
			}
		}
	}


	if ( toggle_state )
		hud_squadmsg_toggle();
}
