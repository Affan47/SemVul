display( void )
{


  if ( _handle_display_on_off )
  {
    _handle_display_on_off = false;

    if ( _display_on )
    {
      for ( int8_t num_win = 0 ; num_win < NB_WIN ; num_win++ )
      {
        if ( _win[num_win] != NULL )
        {

          Window aWindow;
          int x_return, y_return;
          int dest_x_return, dest_y_return;
          unsigned int border_width_return, depth_return;
          XGetGeometry( _display, _win[num_win]->get_window(), &aWindow, &x_return, &y_return,
                        &_win_size[num_win][0], &_win_size[num_win][1], &border_width_return, &depth_return );
          XTranslateCoordinates( _display, _win[num_win]->get_window(), DefaultRootWindow(_display), 0, 0, &dest_x_return, &dest_y_return, &aWindow );

          _win_pos[num_win][0] = dest_x_return - x_return;
          _win_pos[num_win][1] = dest_y_return - y_return;


          delete _win[num_win];
          _win[num_win] = NULL;
        }

        delete _win;
        _win = NULL;
      }

      _display_on = false;
    }
    else
    {
      _show_window |= 1;
      _new_show_window = _show_window;


      if ( _win == NULL ) initialize();

      for ( int8_t i = 0 ; i < NB_WIN ; i++ )
      {
        if ( get_show_window(i) )
        {
          _win[i] = new ae_X11_window( _display, _screen, _atoms, _win_pos[i][0], _win_pos[i][1], _win_size[i][0], _win_size[i][1], _win_name[i] );
        }
      }

      _display_on = true;
    }
  }


  handle_events();


  if ( _display_on )
  {
    for ( int8_t i = 0 ; i < NB_WIN ; i++ )
    {
      if ( get_show_window( i ) )
      {
        if ( get_new_show_window( i ) )
        {
          draw_window( i );
        }
        else
        {
          refresh_window( i );
        }
      }
    }


    XFlush( _display );
  }
}
