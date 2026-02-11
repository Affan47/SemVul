grab(Fl_Window* win) {
  if (win) {
    if (!grab_) {
#ifdef WIN32
      SetActiveWindow(fl_capture = fl_xid(first_window()));
      SetCapture(fl_capture);
#elif defined(__APPLE__)
      fl_capture = fl_xid( first_window() );
      SetUserFocusWindow( fl_capture );
#else
      XGrabPointer(fl_display,
		   fl_xid(first_window()),
		   1,
		   ButtonPressMask|ButtonReleaseMask|
		   ButtonMotionMask|PointerMotionMask,
		   GrabModeAsync,
		   GrabModeAsync,
		   None,
		   0,
		   fl_event_time);
      XGrabKeyboard(fl_display,
		    fl_xid(first_window()),
		    1,
		    GrabModeAsync,
		    GrabModeAsync,
		    fl_event_time);
#endif
    }
    grab_ = win;
  } else {
    if (grab_) {
#ifdef WIN32
      fl_capture = 0;
      ReleaseCapture();
#elif defined(__APPLE__)
      fl_capture = 0;
      SetUserFocusWindow( (WindowRef)kUserFocusAuto );
#else
      XUngrabKeyboard(fl_display, fl_event_time);
      XUngrabPointer(fl_display, fl_event_time);


      XFlush(fl_display);
#endif
      grab_ = 0;
      fl_fix_focus();
    }
  }
}
