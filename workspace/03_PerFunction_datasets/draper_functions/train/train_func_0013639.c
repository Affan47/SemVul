FetchEvent( SDL_Event &event ) {
  GUI_Status rc;

  do {
    if ( SDL_WaitEvent( &event ) ) {


      if ( event.type == SDL_MOUSEMOTION ) {
        SDL_Event next;
        Uint32 start = SDL_GetTicks();

        do {
          int got = SDL_PeepEvents( &next, 1, SDL_GETEVENT, SDL_MOUSEMOTIONMASK );

          if ( got > 0 ) {
            event.motion.x = next.motion.x;
            event.motion.y = next.motion.y;
            event.motion.xrel += next.motion.xrel;
            event.motion.yrel += next.motion.yrel;
          } else break;

        } while ( SDL_GetTicks() - start < 10 );
      }

      rc = SystemFilter( event );

      if ( rc != GUI_NONE ) {
        if ( filter ) {
          rc = filter( event, static_cast<Window *>(windows.Head()) );
        } else rc = GUI_OK;
      }
    } else rc = GUI_ERROR;
  } while ( rc == GUI_NONE );

  return rc;
}
