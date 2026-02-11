medal_main_init(player *pl, int mode)
{
	int idx;
	Assert(pl != NULL);
	Medals_player = pl;
	Player_score = &Medals_player->stats;

#ifndef NDEBUG
	if (Cmdline_gimme_all_medals){
		for (idx=0; idx < MAX_MEDALS; idx++){
			Medals_player->stats.medals[idx] = 1;
		}
	}
#endif

	Medals_mode = mode;
	snazzy_menu_init();
	Medals_window.create( 0, 0, gr_screen.max_w_unscaled, gr_screen.max_h_unscaled, 0 );


	for (idx=0; idx<MEDALS_NUM_BUTTONS; idx++) {

		Medals_buttons[gr_screen.res][idx].button.create(&Medals_window, "", Medals_buttons[gr_screen.res][idx].x, Medals_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);


		Medals_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);


		Medals_buttons[gr_screen.res][idx].button.set_bmaps(Medals_buttons[gr_screen.res][idx].filename);


		Medals_buttons[gr_screen.res][idx].button.link_hotspot(Medals_buttons[gr_screen.res][idx].hotspot);
	}


	for (idx=0; idx<MEDALS_NUM_TEXT; idx++) {
		Medals_window.add_XSTR(&Medals_text[gr_screen.res][idx]);
	}

	Init_flags = 0;

	Medals_bitmap = bm_load(Medals_background_filename[gr_screen.res]);
	if (Medals_bitmap < 0) {
		Error(LOCATION, "Error loading medal background bitmap %s", Medals_background_filename[gr_screen.res]);
	} else {
		Init_flags |= MEDAL_BITMAP_INIT;
	}

	Medals_mask_w = -1;
	Medals_mask_h = -1;

	Medals_bitmap_mask = bm_load(Medals_mask_filename[gr_screen.res]);
	if (Medals_bitmap_mask < 0) {
		Error(LOCATION, "Error loading medal mask file %s", Medals_mask_filename[gr_screen.res]);
	} else {
		Init_flags |= MASK_BITMAP_INIT;
		Medals_mask = bm_lock(Medals_bitmap_mask, 8, BMP_AABITMAP);
		bm_get_info(Medals_bitmap_mask, &Medals_mask_w, &Medals_mask_h);
	}
	init_medal_bitmaps();
	init_snazzy_regions();

	gr_set_color_fast(&Color_normal);

	Medals_window.set_mask_bmap(Medals_mask_filename[gr_screen.res]);
}
