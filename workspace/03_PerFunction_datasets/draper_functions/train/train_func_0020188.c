create(UI_WINDOW *wnd, char *_text, int _x, int _y, int _w, int _h, int do_repeat, int ignore_focus)
{
	text = NULL;

	if (_text) {
		if ( _text[0] != '\0' ) {
			text = vm_strdup(_text);
		}
	}


	base_create( wnd, UI_KIND_BUTTON, _x, _y, _w, _h );


	m_flags = 0;
	next_repeat = 0;
	m_just_highlighted_function = NULL;
	m_disabled_function = NULL;
	if (do_repeat) {
		m_flags |= BF_REPEATS;
		next_repeat = 1;
	}

	m_press_linger = 1;
	first_callback = 1;

	hotkey_if_focus = KEY_SPACEBAR;

	if (ignore_focus){
		m_flags |= BF_IGNORE_FOCUS;
	}

	custom_cursor_bmap = -1;
	previous_cursor_bmap = -1;
}
