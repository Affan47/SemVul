update_ui_screen( void )
{
  static int frame_count = 0;
  int scale = machine_current->timex ? 2 : 1;
  size_t i;
  struct rectangle *ptr;

  if( settings_current.frame_rate <= ++frame_count ) {
    frame_count = 0;
    if( movie_recording ) {
      movie_start_frame();
    }

    if( display_redraw_all ) {
      if( movie_recording ) {
        movie_add_area( 0, 0, DISPLAY_ASPECT_WIDTH >> 3,
                        DISPLAY_SCREEN_HEIGHT );
      }
      uidisplay_area( 0, 0,
                      scale * DISPLAY_ASPECT_WIDTH,
                      scale * DISPLAY_SCREEN_HEIGHT );
      display_redraw_all = 0;
    } else {
      for( i = 0, ptr = rectangle_inactive;
           i < rectangle_inactive_count;
           i++, ptr++ ) {
            if( movie_recording ) {
              movie_add_area( ptr->x, ptr->y, ptr->w, ptr->h );
            }
              uidisplay_area( 8 * scale * ptr->x, scale * ptr->y,
                        8 * scale * ptr->w, scale * ptr->h );
      }
    }

    rectangle_inactive_count = 0;

    uidisplay_frame_end();
  }
}
