Create( short w, short h, int bpp, unsigned long flags ) {
  if ( s_surface ) SDL_FreeSurface( s_surface );
  s_surface = SDL_CreateRGBSurface( flags, w, h, bpp, 0, 0, 0, 0 );
  if ( s_surface == 0 ) return -1;
  this->w = s_surface->w;
  this->h = s_surface->h;
  return 0;
}
