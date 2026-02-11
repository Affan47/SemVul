PG_Application()
		: my_quitEventLoop(false), emergencyQuit(false), enableAppIdleCalls(false) {


#ifdef ENABLE_UNICODE
	setlocale(LC_CTYPE, "C.UTF-8");
#endif

	if(pGlobalApp != NULL) {
		PG_LogWRN("PG_Application Object already exists !");
		exit(-1);
	}

	atexit(PARAGUI_ShutDownCode);


#ifdef WIN32
#ifndef __GNUC__

	SDL_RegisterApp("ParaGUI", 0, GetModuleHandle(NULL));
#endif
#endif


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) < 0) {
		std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	pGlobalApp = this;
	screen = NULL;

	mutexScreen = SDL_CreateMutex();
	my_background = NULL;
	my_freeBackground = false;
	my_backmode = PG_Draw::TILE;
	my_defaultEventSupplier = new PG_SDLEventSupplier;
	my_eventSupplier = my_defaultEventSupplier;


	AddArchive(GetBaseDir());
}
