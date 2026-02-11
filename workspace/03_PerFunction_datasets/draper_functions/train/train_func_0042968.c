drawNukeEffect() {

  int timeFromMaximum = (NUKE_EFFECT_DURATION / 2) - (timeNukeEnd - SDL_GetTicks());
  timeFromMaximum = abs(timeFromMaximum);
  SDL_SetAlpha( nukeEffectSurface, SDL_SRCALPHA | SDL_RLEACCEL,
		lroundf(((NUKE_EFFECT_DURATION / 2) - timeFromMaximum) * 128.0 /
			(NUKE_EFFECT_DURATION / 2)) );
  SDL_BlitSurface( nukeEffectSurface, 0, screen, 0 );

  int randRange = (int)
    (( ((NUKE_EFFECT_DURATION / 2.0) - timeFromMaximum) * NUKE_QUAKE_EFFECT /
	     (NUKE_EFFECT_DURATION / 2.0 ) ) + 0.5);

  int randX, randY;
  if ( randRange == 0 ) randRange = 1;
  randX = (rand() % randRange) - randRange / 2;
  randY = (rand() % randRange) - randRange / 2;

  SDL_Rect src, dest;
  if ( randX < 0 ) {
    src.x = -randX;
    src.w = screen->w + randX;
    dest.x = 0;
    dest.w = screen->w + randX;
  } else {
    src.x = 0;
    src.w = screen->w - randX;
    dest.x = randX;
    dest.w = screen->w - randX;
  }
  if ( randY < 0 ) {
    src.y = -randY;
    src.h = screen->h + randY;
    dest.y = 0;
    dest.h = screen->h + randY;
  } else {
    src.y = 0;
    src.h = screen->h - randY;
    dest.y = randY;
    dest.h = screen->h - randY;
  }

  SDL_BlitSurface( screen, &src, screen, &dest );
}
