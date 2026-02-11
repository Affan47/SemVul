multi_pxo_help_init()
{
	int idx;


	Multi_pxo_help_bitmap = bm_load(Multi_pxo_help_fname[gr_screen.res]);
	if(Multi_pxo_help_bitmap < 0){

		Int3();
	}


	Multi_pxo_help_window.create(0,0,gr_screen.max_w,gr_screen.max_h,0);
	Multi_pxo_help_window.set_mask_bmap(Multi_pxo_help_mask_fname[gr_screen.res]);


	for(idx=0; idx<MULTI_PXO_HELP_NUM_BUTTONS; idx++){

		Multi_pxo_help_buttons[gr_screen.res][idx].button.create(&Multi_pxo_help_window, "", Multi_pxo_help_buttons[gr_screen.res][idx].x, Multi_pxo_help_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);


		Multi_pxo_help_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);


		Multi_pxo_help_buttons[gr_screen.res][idx].button.set_bmaps(Multi_pxo_help_buttons[gr_screen.res][idx].filename);


		Multi_pxo_help_buttons[gr_screen.res][idx].button.link_hotspot(Multi_pxo_help_buttons[gr_screen.res][idx].hotspot);
	}


	for(idx=0; idx<MULTI_PXO_HELP_NUM_TEXT; idx++){
		Multi_pxo_help_window.add_XSTR(&Multi_pxo_help_text[gr_screen.res][idx]);
	}

	multi_pxo_help_load();


	Multi_pxo_help_cur = 0;
}
