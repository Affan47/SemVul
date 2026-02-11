PumpIntoEventQueue(const SDL_Event* event) {
	PG_Widget* widget = NULL;


	if((event->type != SDL_USEREVENT) && (event->type != SDL_VIDEORESIZE)) {
		if(captureObject) {
			return captureObject->ProcessEvent(event);
		}
	}

	switch(event->type) {

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if(inputFocusObject) {

				if(inputFocusObject->ProcessEvent(event)) {
					return true;
				}

			}
			break;

		case SDL_MOUSEMOTION:
			widget = PG_Widget::FindWidgetFromPos(event->motion.x, event->motion.y);

			if(lastwidget && (lastwidget != widget)) {
				lastwidget->eventMouseLeave();
				lastwidget = NULL;
			}

			if(widget) {
				lastwidget = widget;
				widget->ProcessEvent(event);
				return true;
			}
			return true;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			widget = PG_Widget::FindWidgetFromPos(event->button.x, event->button.y);
			if(widget) {
				widget->ProcessEvent(event);
				return true;
			}
			break;
	}


	if(ProcessEvent(event)) {
		return true;
	}


	bool processed = false;
	PG_Widget* list = PG_Widget::GetWidgetList()->first();

	PG_Widget* o = NULL;
	while(list != NULL) {
		o = list;


		if(o->ProcessEvent(event)) {
			processed = true;
			break;
		}
		list = list->next();
	}

	return processed;
}
