multi_pause_init()
{
	int i;


	if ( Multi_paused ) {
		return;
	}

	Assert( Game_mode & GM_MULTIPLAYER );

	if ( !(Game_mode & GM_MULTIPLAYER) )
		return;


	weapon_pause_sounds();


	if (Game_mode & GM_STANDALONE_SERVER) {
		std_debug_set_standalone_state_string("Multi paused do");
	}

	else {

		audiostream_pause_all();


		multi_msg_text_flush();

		if ( Multi_paused_screen_id == -1 )
			Multi_paused_screen_id = gr_save_screen();


		Multi_paused_window.create(0, 0, gr_screen.max_w_unscaled, gr_screen.max_h_unscaled, 0);
		Multi_paused_window.set_mask_bmap(Multi_paused_bg_mask[gr_screen.res]);
		Multi_paused_background = bm_load(Multi_paused_bg_fname[gr_screen.res]);

		for (i=0; i<MULTI_PAUSED_NUM_BUTTONS; i++) {

			Multi_paused_buttons[gr_screen.res][i].button.create(&Multi_paused_window, "", Multi_paused_buttons[gr_screen.res][i].x, Multi_paused_buttons[gr_screen.res][i].y, 1, 1, 0, 1);


			Multi_paused_buttons[gr_screen.res][i].button.set_highlight_action(common_play_highlight_sound);


			Multi_paused_buttons[gr_screen.res][i].button.set_bmaps(Multi_paused_buttons[gr_screen.res][i].filename);


			Multi_paused_buttons[gr_screen.res][i].button.link_hotspot(Multi_paused_buttons[gr_screen.res][i].hotspot);
		}


		for(i=0; i<MULTI_PAUSED_NUM_TEXT; i++){
			Multi_paused_window.add_XSTR(&Multi_paused_text[gr_screen.res][i]);
		}


		chatbox_close();


		chatbox_create(CHATBOX_FLAG_MULTI_PAUSED);
	}

	Multi_paused = 1;


	multi_reset_timestamps();
}
