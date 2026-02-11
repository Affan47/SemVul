menu_on()
{
  Window r, c;
  int rx, ry, x, y;
  unsigned int m;

  if(scr->menubarparent) {
    XMapRaised(dpy, scr->menubarparent);
    XRaiseWindow(dpy, scr->menubar);
    XGrabPointer(dpy, scr->back, True, ButtonPressMask|ButtonReleaseMask|
		EnterWindowMask|LeaveWindowMask, GrabModeAsync, GrabModeAsync,
		scr->back, wm_curs, CurrentTime);
    XSetInputFocus(dpy, scr->menubar, RevertToParent, CurrentTime);
    if(XQueryPointer(dpy, scr->menubarparent, &r, &c, &rx, &ry, &x, &y, &m))
      menubar_enter(c);
  }
}
