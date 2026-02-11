player_select_do()
{
	int k;


	if ((Global_warning_count > 10 || Global_error_count > 0) && !Startup_warning_dialog_displayed) {
		char text[512];
		sprintf(text, "Warning!\n\nThe currently active mod has generated %d warnings and/or errors during program startup.  These could have been caused by anything from incorrectly formated table files to corrupt models.  While FreeSpace Open will attempt to compensate for these issues, it cannot guarantee a trouble-free gameplay experience.  Source Code Project staff cannot provide assistance or support for these problems, as they are caused by the mod's data files, not FreeSpace Open's source code.", Global_warning_count + Global_error_count);
		popup(PF_TITLE_BIG | PF_TITLE_RED, 1, POPUP_OK, text);
		Startup_warning_dialog_displayed = true;
	}


	if (Player_select_input_mode) {
		Player_select_input_box.set_focus();
	}


	k = Player_select_window.process();

	if (k) {
		extern void game_process_cheats(int k);
		game_process_cheats(k);
	}

	switch (k) {

		case KEY_TAB: {
			if (Player_select_input_mode) {
				gamesnd_play_iface(SND_GENERAL_FAIL);
				break;
			}


			gamesnd_play_iface(SND_USER_SELECT);

			if (Player_select_mode == PLAYER_SELECT_MODE_MULTI) {
				player_select_set_bottom_text(XSTR( "Single-Player Mode", 376));


				player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
			} else if (Player_select_mode == PLAYER_SELECT_MODE_SINGLE) {
				player_select_set_bottom_text(XSTR( "Multiplayer Mode", 377));


				player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
			}

			break;
		}

		case KEY_ESC: {


			if ( !Player_select_input_mode ) {
				Player_select_no_save_pilot = 1;
			}

			break;
		}
	}


	gr_set_bitmap(Player_select_background_bitmap);
	gr_bitmap(0,0);


	if (Player_select_autoaccept) {
		Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].button.press_button();
	}


	Player_select_window.draw();


	if (Player_select_mode == PLAYER_SELECT_MODE_SINGLE) {
		Player_select_buttons[gr_screen.res][SINGLE_BUTTON].button.draw_forced(2);
	} else {
		Player_select_buttons[gr_screen.res][MULTI_BUTTON].button.draw_forced(2);
	}


	player_select_draw_list();


	player_select_display_copyright();

	if (!Player_select_input_mode) {
		player_select_process_noninput(k);
	} else {
		player_select_process_input(k);
	}


	player_select_display_all_text();

	gr_flip();
}
