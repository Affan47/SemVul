place( const MapCoordinate& mc ) const
{
   if ( !actmap->getField(mc)->addobject( item ) )
      if ( SDL_GetKeyState(NULL)[SDLK_LCTRL] || SDL_GetKeyState(NULL)[SDLK_RCTRL] || choice_dlg("object cannot be built here\n(bypass this dialog by pressing <ctrl>)","~c~ancel","~i~gnore") == 2)
         actmap->getField(mc)->addobject( item, -1, true );

   return 0;
}
