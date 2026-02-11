Shutdown() {
	DeleteBackground();


	PG_Widget* list = PG_Widget::GetWidgetList()->first();

	while((list = PG_Widget::GetWidgetList()->first()) != NULL) {
		delete list;
	}


	if(my_Theme) {
		delete my_Theme;
		my_Theme = NULL;
	}


	SDL_DestroyMutex(mutexScreen);


	delete DefaultFont;
	DefaultFont = NULL;


	UnloadSurface(my_mouse_backingstore);
	my_mouse_backingstore = NULL;
}
