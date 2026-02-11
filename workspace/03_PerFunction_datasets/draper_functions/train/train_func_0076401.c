button_handle_event(struct widget *w, SDL_Event *event)
{
	struct widget_button *b = WIDGET_BUTTON(w);
	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:

			b->state = PRESSED;
			return 1;

		case SDL_MOUSEBUTTONUP:

			if (b->state == PRESSED) {
				b->state = HOVERED;
				if (event->button.button == MOUSE_BUTTON_1)
					if (b->activate_button)
						b->activate_button(b);
				if (event->button.button == MOUSE_BUTTON_3)
					if (b->activate_button_secondary)
						b->activate_button_secondary(b);
			}
			break;

		case SDL_USEREVENT:

			if (event->user.code == EVENT_MOUSE_ENTER) {
				b->state = HOVERED;

				widget_set_tooltip(&b->tooltip, &w->rect);
			}

			if (event->user.code == EVENT_MOUSE_LEAVE) {
				b->state = DEFAULT;
				widget_set_tooltip(NULL, NULL);
			}
			if (event->user.code == EVENT_UPDATE && w->update)
				w->update(w);
			break;

		default:
			break;
	}
	return 0;
}
