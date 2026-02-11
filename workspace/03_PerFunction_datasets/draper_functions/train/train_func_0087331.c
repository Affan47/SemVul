ToggleFullscreen ()
{
  if (_embedded)
    return;

  Window childWindow;
  XWindowAttributes xwattributes;

  int newX = 0;
  int newY = 0;
  int newWidth = 0;
  int newHeight = 0;

  if (_state.fullscreen) {


    if (!(_wmType & wm_FULLSCREEN)) {

      newX = _state.oldx;
      newY = _state.oldy;
      newWidth = _state.oldWidth;
      newHeight = _state.oldHeight;
      SetDecoration (true);
    }


    SetEWMHFullscreen (_NET_WM_STATE_REMOVE);
  }
  else {


    SetEWMHFullscreen (_NET_WM_STATE_ADD);


    if (!(_wmType & wm_FULLSCREEN)) {

      XLockDisplay (_display);

      newX = 0;
      newY = 0;
      newWidth = DisplayWidth (_display, DefaultScreen (_display));
      newHeight = DisplayHeight (_display, DefaultScreen (_display));

      SetDecoration (false);
      XFlush (_display);

      XTranslateCoordinates (_display, _XWindow, RootWindow (_display, DefaultScreen (_display)),
                             0, 0, &_state.oldx, &_state.oldy, &childWindow);

      XGetWindowAttributes (_display, _XWindow, &xwattributes);
      XUnlockDisplay (_display);

      _state.oldWidth = xwattributes.width;
      _state.oldHeight = xwattributes.height;
    }
  }


  if (!(_wmType & wm_FULLSCREEN)) {

    SetSizeHints (newX, newY, _XImage->width, _XImage->height, newWidth, newHeight);

    XLockDisplay (_display);
    SetLayer (!_state.fullscreen ? 0 : 1);
    XMoveResizeWindow (_display, _XWindow, newX, newY, newWidth, newHeight);
    XUnlockDisplay (_display);
  }


  if (_state.fullscreen & _state.ontop)
    SetLayer (1);

  XLockDisplay (_display);
  XMapRaised (_display, _XWindow);
  XRaiseWindow (_display, _XWindow);
  XSync (_display, False);
  XUnlockDisplay (_display);

  _state.fullscreen = !_state.fullscreen;
}
