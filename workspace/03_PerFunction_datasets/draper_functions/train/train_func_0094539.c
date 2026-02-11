leveleditor_select_input(SDL_Event * event)
{
	if(!mouse_in_level)
		return 0;

	if (mode != DISABLED) {
		if (EVENT_LEFT_RELEASE(event) || EVENT_KEYPRESS(event, SDLK_ESCAPE)) {

			leveleditor_select_reset();
			return 1;
		}
	}

	switch (mode) {
	case DISABLED:
		if (EVENT_LEFT_PRESS(event)) {
			start_rect_select();
			return 0;
		}
		break;
	case FD_RECT:
		if (EVENT_MOVE(event)) {
			do_rect_select();
			return 0;
		}
		break;
	case FD_RECTDONE:
		if (EVENT_LEFT_PRESS(event)) {
			if (ShiftPressed()) {
				start_drag_drop();
			} else {
				if (!CtrlPressed()) {
					clear_selection(-1);
				}
				start_rect_select();
			}
			return 0;
		}
		break;
	case DRAGDROP:
		if (EVENT_MOVE(event)) {
			do_drag_drop();
			return 0;
		}
		break;
	}

	return 0;
}
