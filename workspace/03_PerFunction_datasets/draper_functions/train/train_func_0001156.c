SetLayer (int layer)
{
  char *state = NULL;

  Window mRootWin = RootWindow (_display, DefaultScreen (_display));
  XEvent xev;
  memset (&xev, 0, sizeof(xev));

  if (_wmType & wm_LAYER) {

    if (!_state.origLayer)
      _state.origLayer = GetGnomeLayer ();

    xev.type = ClientMessage;
    xev.xclient.display = _display;
    xev.xclient.window = _XWindow;
    xev.xclient.message_type = XA_WIN_LAYER;
    xev.xclient.format = 32;
    xev.xclient.data.l [0] = layer ? WIN_LAYER_ABOVE_DOCK : _state.origLayer;
    xev.xclient.data.l [1] = CurrentTime;
    PTRACE(4, "X11\tLayered style stay on top (layer " << xev.xclient.data.l[0] << ")");

    XLockDisplay (_display);
    XSendEvent (_display, mRootWin, FALSE, SubstructureNotifyMask,  &xev);
    XUnlockDisplay (_display);

  }
  else if (_wmType & wm_NETWM) {

    xev.type = ClientMessage;
    xev.xclient.message_type = XA_NET_WM_STATE;
    xev.xclient.display = _display;
    xev.xclient.window = _XWindow;
    xev.xclient.format = 32;
    xev.xclient.data.l [0] = layer;

    if (_wmType & wm_STAYS_ON_TOP)
      xev.xclient.data.l [1] = XA_NET_WM_STATE_STAYS_ON_TOP;
    else
      if (_wmType & wm_ABOVE)
        xev.xclient.data.l [1] = XA_NET_WM_STATE_ABOVE;
    else
      if (_wmType & wm_FULLSCREEN)
        xev.xclient.data.l [1] = XA_NET_WM_STATE_FULLSCREEN;
    else
      if (_wmType & wm_BELOW)
        xev.xclient.data.l [1] = XA_NET_WM_STATE_BELOW;

    XLockDisplay (_display);
    XSendEvent (_display, mRootWin, FALSE, SubstructureRedirectMask, &xev);
    state = XGetAtomName (_display, xev.xclient.data.l [1]);
    PTRACE(4, "X11\tNET style stay on top (layer " << layer << "). Using state " << state );
    XFree (state);
    XUnlockDisplay (_display);
  }
}
