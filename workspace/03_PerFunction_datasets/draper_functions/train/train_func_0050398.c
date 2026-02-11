Action(KeyAction action) {
	int x = my_xpos + my_width / 2;
	int y = my_ypos + my_height / 2;

	switch(action) {
		case ACT_ACTIVATE:
			SDL_WarpMouse(x,y);
			eventMouseEnter();
			break;

		case ACT_DEACTIVATE:
			eventMouseLeave();
			break;

		case ACT_OK:
			SDL_MouseButtonEvent button;
			button.button = 1;
			button.x = x;
			button.y = y;
			eventMouseButtonDown(&button);
			SDL_Delay(200);
			eventMouseButtonUp(&button);
			Action(ACT_ACTIVATE);
			break;

		default:
			break;
	}

	return false;
}
