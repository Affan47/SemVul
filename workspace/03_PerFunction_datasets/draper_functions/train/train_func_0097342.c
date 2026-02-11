popup_play_default_change_sound(popup_info *pi)
{
	if ( pi->nchoices > 1 ) {
		int i, mouse_over=0;
		UI_BUTTON *br, *b;


		for ( i = 0; i < pi->nchoices; i++ ) {
			br = &Popup_button_regions[i];
			b = &Popup_buttons[i];
			if ( br->button_down() ) {
				mouse_over=1;
				break;
			}

			if ( br->button_hilighted() && !b->button_down() ) {
				mouse_over=1;
				break;
			}

			if ( b->button_hilighted() ) {
				mouse_over=1;
			}
		}

		if (!mouse_over) {
			gamesnd_play_iface(SND_USER_SELECT);
		}
	}
}
