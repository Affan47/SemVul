spiegelRect(SDL_Rect & r) {
  if (ld->mSpiegeln) {
    r.y = gry * gric - r.y - r.h;
  }
}
