ppsk_hotkeys(int k)
{

	int hotkey_set;

#ifndef NDEBUG
	k &= ~KEY_DEBUGGED;
#endif

	switch (k) {
		case KEY_F5:
		case KEY_F6:
		case KEY_F7:
		case KEY_F8:
		case KEY_F9:
		case KEY_F10:
		case KEY_F11:
		case KEY_F12:
			hotkey_set = mission_hotkey_get_set_num(k);
			if ( !(Players[Player_num].flags & PLAYER_FLAGS_MSG_MODE) )
				hud_target_hotkey_select( hotkey_set );
			else
				hud_squadmsg_hotkey_select( hotkey_set );

			break;

		case KEY_F5 + KEY_SHIFTED:
		case KEY_F6 + KEY_SHIFTED:
		case KEY_F7 + KEY_SHIFTED:
		case KEY_F8 + KEY_SHIFTED:
		case KEY_F9 + KEY_SHIFTED:
		case KEY_F10 + KEY_SHIFTED:
		case KEY_F11 + KEY_SHIFTED:
		case KEY_F12 + KEY_SHIFTED:
			hotkey_set = mission_hotkey_get_set_num(k&(~KEY_SHIFTED));
			mprintf(("Adding to set %d\n", hotkey_set+1));
			if ( Player_ai->target_objnum == -1)
				HUD_sourced_printf(HUD_SOURCE_HIDDEN, XSTR( "No target to add/remove from set %d.", 26), hotkey_set+1);
			else  {
				hud_target_hotkey_add_remove( hotkey_set, &Objects[Player_ai->target_objnum], HOTKEY_USER_ADDED);
				HUD_sourced_printf(HUD_SOURCE_HIDDEN, XSTR( "%s added to set %d. (F%d)", 27), Ships[Objects[Player_ai->target_objnum].instance].ship_name, hotkey_set, 4+hotkey_set+1);
			}

			break;

		case KEY_F5 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F6 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F7 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F8 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F9 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F10 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F11 + KEY_SHIFTED + KEY_ALTED:
		case KEY_F12 + KEY_SHIFTED + KEY_ALTED:
			hotkey_set = mission_hotkey_get_set_num(k & ~KEY_SHIFTED+KEY_ALTED);
			hud_target_hotkey_clear( hotkey_set );
			break;

		case KEY_SHIFTED + KEY_MINUS:
			if ( HUD_color_alpha > HUD_COLOR_ALPHA_USER_MIN )	{
				HUD_color_alpha--;
				HUD_init_colors();
			}
			break;

		case KEY_SHIFTED + KEY_EQUAL:
			if ( HUD_color_alpha < HUD_COLOR_ALPHA_USER_MAX ) {
				HUD_color_alpha++;
				HUD_init_colors();
			}
			break;
	}
}
