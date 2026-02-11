ui_event( void )
{
  SDL_Event event;

  while ( SDL_PollEvent( &event ) ) {
    switch ( event.type ) {
    case SDL_KEYDOWN:
      sdlkeyboard_keypress( &(event.key) );
      break;
    case SDL_KEYUP:
      sdlkeyboard_keyrelease( &(event.key) );
      break;

    case SDL_MOUSEBUTTONDOWN:
      ui_mouse_button( event.button.button, 1 );
      break;
    case SDL_MOUSEBUTTONUP:
      ui_mouse_button( event.button.button, 0 );
      break;
    case SDL_MOUSEMOTION:
      if( ui_mouse_grabbed ) {
        ui_mouse_motion( event.motion.x - 128, event.motion.y - 128 );
        if( event.motion.x != 128 || event.motion.y != 128 )
          SDL_WarpMouse( 128, 128 );
      }
      break;

#if defined USE_JOYSTICK && !defined HAVE_JSW_H

    case SDL_JOYBUTTONDOWN:
      sdljoystick_buttonpress( &(event.jbutton) );
      break;
    case SDL_JOYBUTTONUP:
      sdljoystick_buttonrelease( &(event.jbutton) );
      break;
    case SDL_JOYAXISMOTION:
      sdljoystick_axismove( &(event.jaxis) );
      break;

#endif

    case SDL_QUIT:
      fuse_emulation_pause();
      menu_file_exit(0);
      fuse_emulation_unpause();
      break;
    case SDL_VIDEOEXPOSE:
      display_refresh_all();
      break;
    case SDL_ACTIVEEVENT:
      if( event.active.state & SDL_APPINPUTFOCUS ) {
	if( event.active.gain ) ui_mouse_resume(); else ui_mouse_suspend();
      }
      break;
    default:
      break;
    }
  }

  return 0;
}
