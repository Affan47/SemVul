multi_ingame_select_do()
{


	int k = Multi_ingame_window.process();


	switch(k){
	case KEY_ESC :
		multi_quit_game(PROMPT_CLIENT);
		break;

	case KEY_UP:
		multi_ingame_scroll_select_up();
		break;

	case KEY_DOWN:
		multi_ingame_scroll_select_down();
		break;
	}


	multi_ingame_join_check_buttons();


	multi_ingame_ship_list_process();


	gr_reset_clip();
	GR_MAYBE_CLEAR_RES(Multi_ingame_bitmap);
	if(Multi_ingame_bitmap != -1){
		gr_set_bitmap(Multi_ingame_bitmap);
		gr_bitmap(0,0);
	}
	Multi_ingame_window.draw();


	multi_ingame_handle_timeout();


	multi_ingame_join_display_avail();


	gr_flip();
}
