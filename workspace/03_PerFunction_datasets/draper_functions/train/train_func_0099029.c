key_event( GtkWidget *input, GdkEventKey *event )
{
  XKeyEvent xevent;

  switch( event->type )
  {
    case GDK_KEY_PRESS:
      xevent.type = KeyPress;
      break;

    case GDK_KEY_RELEASE:
      xevent.type = KeyRelease;
      break;

    default:
      return FALSE;
  }

  xevent.display = gdk_x11_get_default_xdisplay();
  xevent.keycode = event->hardware_keycode;
  xevent.state = event->state;
  xevent.time = event->time;
  xevent.root = gdk_x11_get_default_root_xwindow();

  window_list_foreach_selected( wl, window_list_foreach_callback, &xevent );

  return TRUE;
}
