MouseDown( const SDL_MouseButtonEvent &button ) {
  short mx = button.x - surface->LeftEdge();
  short my = button.y - surface->TopEdge();

  if ( Contains( mx, my ) ) {
    if ( button.button == SDL_BUTTON_LEFT ) {
      if ( knob.Contains( mx, my ) ) {
        Push();
        mousehit = true;
      } else {
        short diff = MAX( 1, size/2 );
        if ( flags & WIDGET_HSCROLL ) {
          if ( mx < knob.x ) ScrollTo( current - diff );
          else if ( mx >= (knob.x + knob.w) ) ScrollTo( current + diff );
        } else {
          if ( my < knob.y ) ScrollTo( current - diff );
          else if ( my >= (knob.y + knob.h) ) ScrollTo( current + diff );
        }
      }
    } else if ( button.button == SDL_BUTTON_WHEELUP ) {
      ScrollTo( current - MAX(1, size/4) );
    } else if ( button.button == SDL_BUTTON_WHEELDOWN ) {
      ScrollTo( current + MAX(1, size/4) );
    }
  }

  return GUI_OK;
}
