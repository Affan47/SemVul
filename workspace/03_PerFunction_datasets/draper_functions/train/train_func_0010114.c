UpdateRect(const PG_Rect& r) {
	if(PG_Application::GetBulkMode()) {
		return;
	}

	SDL_Surface* screen = PG_Application::GetScreen();

   PG_Application::ScreenLocker locker(true);
	PG_Application::RedrawBackground(r);
	SDL_SetClipRect(screen, (PG_Rect*)&r);
	widgetList.Blit(r);
	SDL_SetClipRect(screen, NULL);
}
