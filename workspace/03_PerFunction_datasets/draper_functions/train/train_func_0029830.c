boundS(int & x, int & y) {
    if (x<0) x=0;
    if (y<0) y=0;
    SDL_Surface * screen = SDL_GetVideoSurface();
    if (x>screen->w) x=screen->w;
    if (y>screen->h) y=screen->h;
  }
