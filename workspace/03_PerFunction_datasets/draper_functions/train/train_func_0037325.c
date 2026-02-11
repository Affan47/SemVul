multi_ingame_select_init()
{


	int idx;

	Multi_ingame_join_sig = 0;
	Net_player->m_player->objnum = -1;


	multi_ingame_load_icons();


	memset(Multi_ingame_ship_sigs,0,sizeof(ushort) * MAX_PLAYERS);


	Multi_ingame_ship_selected = -1;


	Ingame_time_left = timestamp(MULTI_INGAME_TIME_SECONDS);


	Multi_ingame_window.create(0,0,gr_screen.max_w_unscaled,gr_screen.max_h_unscaled,0);
	Multi_ingame_window.set_mask_bmap(Multi_ingame_join_bitmap_mask_fname[gr_screen.res]);


	Multi_ingame_bitmap = bm_load(Multi_ingame_join_bitmap_fname[gr_screen.res]);
	if(Multi_ingame_bitmap < 0)
		Error(LOCATION, "Couldn't load background bitmap for ingame join");


	for(idx=0; idx<MULTI_INGAME_JOIN_NUM_BUTTONS; idx++) {

		Multi_ingame_join_buttons[gr_screen.res][idx].button.create(&Multi_ingame_window, "", Multi_ingame_join_buttons[gr_screen.res][idx].x, Multi_ingame_join_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);


		Multi_ingame_join_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);


		Multi_ingame_join_buttons[gr_screen.res][idx].button.set_bmaps(Multi_ingame_join_buttons[gr_screen.res][idx].filename);


		Multi_ingame_join_buttons[gr_screen.res][idx].button.link_hotspot(Multi_ingame_join_buttons[gr_screen.res][idx].hotspot);
	}


	for(idx=0; idx<MULTI_INGAME_JOIN_NUM_TEXT; idx++) {
		Multi_ingame_window.add_XSTR(&Multi_ingame_join_text[gr_screen.res][idx]);
	}


	Multi_ingame_select_button.create(&Multi_ingame_window, "", Mi_name_field[gr_screen.res][MI_FIELD_X], Mi_name_field[gr_screen.res][MI_FIELD_Y], Mi_width[gr_screen.res], Mi_height[gr_screen.res], 0, 1);
	Multi_ingame_select_button.hide();


}
