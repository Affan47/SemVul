group_keyboard_event(struct widget *wg, SDL_Event *event)
{
	struct widget *w;

	list_for_each_entry_reverse(w, &WIDGET_GROUP(wg)->list, node) {
		if (w->enabled && w->handle_event(w, event)) {
			return 1;
		}
	}
	return 0;
}
