execute()
{
   if ( *mouseUpdateFlag )
      SDL_ShowCursor( 0 );

   SDL_UpdateRects( screen, numrects, rects);
   postScreenUpdate( screen );

   if ( *mouseUpdateFlag )
      SDL_ShowCursor( 1 );
}
