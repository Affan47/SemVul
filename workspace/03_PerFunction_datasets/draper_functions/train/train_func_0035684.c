noClip() {
    if (mActDepth == 0) {


      SDL_Surface * s = SDL_GetVideoSurface();
      SDL_Rect r = SDLTools::rect(0, 0, s->w, s->h);
      SDL_SetClipRect(s, &r);
    } else
      setClipRectV(mBounds[mActDepth]);
  }
