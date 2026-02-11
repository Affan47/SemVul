eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	int x,y;

	if(button->button == 1) {
		PG_Application::GetEventSupplier()->GetMouseState(x,y);
		offset = ScreenToClient(x, y);
	}

	return PG_Button::eventMouseButtonDown(button);
}
