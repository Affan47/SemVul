local_io_update(Local_io *io) {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handle_event(io, event.key);
				break;
			default:
				break;
		}
	}
	return;
}
