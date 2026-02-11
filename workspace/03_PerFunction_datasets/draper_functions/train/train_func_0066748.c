init_sdl(int iFlags)
{
  bool error;
  Main.screen = NULL;
  Main.guis = NULL;
  Main.gui = NULL;
  Main.map = NULL;
  Main.dummy = NULL;
  Main.rects_count = 0;
  Main.guis_count = 0;

  if (SDL_WasInit(SDL_INIT_AUDIO)) {
    error = (SDL_InitSubSystem(iFlags) < 0);
  } else {
    error = (SDL_Init(iFlags) < 0);
  }
  if (error) {
    log_fatal(_("Unable to initialize SDL library: %s"), SDL_GetError());
    exit(1);
  }

  atexit(SDL_Quit);


  if (TTF_Init() < 0) {
    log_fatal(_("Unable to initialize SDL_ttf library: %s"), SDL_GetError());
    exit(2);
  }

  atexit(TTF_Quit);
}
