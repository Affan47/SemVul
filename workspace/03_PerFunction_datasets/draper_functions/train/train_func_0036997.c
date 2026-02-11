chatbox_create(int mode_flags)
{
	int idx;


	if (Chatbox_created){
		return -1;
	}


	Assert(Game_mode & GM_MULTIPLAYER);


	chatbox_set_mode(mode_flags);


	chatbox_chat_init();


	if(Chatbox_mode_flags & CHATBOX_FLAG_DRAW_BOX){
		Chatbox_big_bitmap = bm_load(Chatbox_big_bitmap_fname[gr_screen.res]);
		Chatbox_small_bitmap = bm_load(Chatbox_small_bitmap_fname[gr_screen.res]);
		Chatbox_mp_bitmap = bm_load(Chatbox_p_bitmap_fname[gr_screen.res]);

		if(Chatbox_mode_flags & CHATBOX_FLAG_SMALL){
			Chatbox_bitmap = Chatbox_small_bitmap;
		} else if(Chatbox_mode_flags & CHATBOX_FLAG_BIG){
			Chatbox_bitmap = Chatbox_big_bitmap;
		} else {
			Chatbox_bitmap = Chatbox_mp_bitmap;
		}

		if((Chatbox_bitmap == -1) || (Chatbox_small_bitmap == -1) || (Chatbox_big_bitmap == -1) || (Chatbox_mp_bitmap == -1)){
			return -1;
		}
	}


	Chat_window.create( 0, 0, gr_screen.max_w_unscaled, gr_screen.max_h_unscaled, 0 );
	Chat_window.set_mask_bmap(Chatbox_mask);


	Chat_inputbox.create( &Chat_window, Chatbox_inputbox_x, Chatbox_textenter_y, Chatbox_inputbox_w, CHATBOX_MAX_LEN, "", UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_ESC_CLR | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_EAT_USED, Chatbox_w, Color_netplayer[MY_NET_PLAYER_NUM]);
	Chat_inputbox.set_focus();
	Chat_inputbox.set_invalid_chars(CHATBOX_INVALID_CHARS);


	if((Chatbox_mode_flags & CHATBOX_FLAG_BUTTONS) && (Chatbox_mode_flags & CHATBOX_FLAG_DRAW_BOX)){
		for(idx=0; idx<CHATBOX_NUM_BUTTONS; idx++){

			Chatbox_buttons[gr_screen.res][idx].button.create(&Chat_window, "", Chatbox_buttons[gr_screen.res][idx].x, Chatbox_buttons[gr_screen.res][idx].y, 60, 30, (idx == CHATBOX_TOGGLE_SIZE) ? 0 : 1);


			Chatbox_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);


			Chatbox_buttons[gr_screen.res][idx].button.set_bmaps(Chatbox_buttons[gr_screen.res][idx].filename);


			Chatbox_buttons[gr_screen.res][idx].button.link_hotspot(Chatbox_buttons[gr_screen.res][idx].hotspot);
		}


		if(Chatbox_mode_flags & CHATBOX_FLAG_SMALL){
			Chatbox_buttons[gr_screen.res][CHATBOX_TOGGLE_SIZE].button.set_bmaps(Chatbox_buttons[gr_screen.res][CHATBOX_TOGGLE_SIZE].filename);
		} else {
			Chatbox_buttons[gr_screen.res][CHATBOX_TOGGLE_SIZE].button.set_bmaps(Chatbox_buttons[gr_screen.res][CHATBOX_TOGGLE_SIZE+1].filename);
		}
	}


	Chat_enter_text.create( &Chat_window, "", 0, 0, 60, 30, 0);
	Chat_enter_text.hide();
	Chat_enter_text.link_hotspot(50);

	Chatbox_created = 1;
	return 0;
}
