menuitem_options(char * notused)
{
	SDL_Event event;

	int rc=popupoptionsmenu();

	if (rc!=POPUPMENUEXITMENU)
	{
		return rc;
	}
	else
	{

		SDL_GetMouseState((int *)&event.motion.x,(int *)&event.motion.y);
		event.type = SDL_MOUSEMOTION;
		SDL_PushEvent(&event);
		return POPUPMENUDONOTHING;
	}
}
