DisplayFormat( void ) {
  SDL_Surface *new_s;

  if ( s_surface == 0 || !SDL_WasInit( SDL_INIT_VIDEO ) )  return -1;
  if ( (new_s = SDL_DisplayFormat( s_surface )) == 0 ) return -1;
  SDL_FreeSurface( s_surface );
  s_surface = new_s;
  return 0;
}
