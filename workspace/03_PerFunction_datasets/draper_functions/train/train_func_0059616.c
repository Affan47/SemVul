execute()
{
   if ( *mouseUpdateFlag )
      SDL_ShowCursor( 0 );

   SDL_Surface* screen = SDL_SetVideoMode(x, y, depth, flags);
   if (screen == NULL)
      screen = SDL_SetVideoMode(x, y, depth, flags & ~SDL_FULLSCREEN );

   srf( screen );
   initASCGraphicSubsystem( screen );

   if ( *mouseUpdateFlag )
      SDL_ShowCursor( 1 );
}
