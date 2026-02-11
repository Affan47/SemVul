MoveMe( x, y )
  Coord  x, y;
  {
    Coord       dx, dy;
    Window      root;
    Coord       top, left, w, h;
    int         border, d;
    XEvent      ev;
    XSizeHints  shint;

    GetWindowGeometry( window, &left, &top, &w, &h, &border );
    dx = x + border;
    dy = y + border;
    border *= 2;
    w += border - 1;
    h += border - 1;

    root = RootWindowOfScreen( screen );
    XGrabServer( display );
    GrabMouse( root, ButtonReleaseMask | ButtonPressMask, cursors.move );

    ev.type = MotionNotify;
    x = left; y = top;
    while( GetMotionEvent( root, &ev, &x, &y ) )
      {
	x -= dx;
	y -= dy;
	MoveOutline( root, x, y, x + w, y + h );
      }
    MoveOutline( root, 0, 0, 0, 0 );

    XUngrabPointer( display, CurrentTime );
    XUngrabServer( display );

    if( ev.type == ButtonPress or (x == left and y == top) )
	return;

    shint.x = x;
    shint.y = y;
    shint.width = w - border + 1;
    shint.height = h - border + 1;
    shint.max_width = shint.max_height = 16000;
    shint.width_inc = shint.height_inc = 1;
    GetMinWsize( &shint.min_width, &shint.min_height );
    shint.flags = ( PMinSize | PMaxSize | PResizeInc | USPosition | USSize );
    XSetNormalHints( display, window, &shint );
    XMoveWindow( display, window, x, y );
  }
