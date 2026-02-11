handle(int event) {
  int newval;
  switch (event) {
  case FL_HIDE:
  case FL_DEACTIVATE:
  case FL_RELEASE:
    newval = 0; goto J1;
  case FL_PUSH:
  case FL_DRAG:
    if (Fl::visible_focus()) Fl::focus(this);
    newval = Fl::event_inside(this);
  J1:
    if (!active())
      newval = 0;
    if (value(newval)) {
      if (newval) {
	Fl::add_timeout(INITIALREPEAT,repeat_callback,this);
	do_callback();
      } else {
	Fl::remove_timeout(repeat_callback,this);
      }
    }
    return 1;
  default:
    return Fl_Button::handle(event);
  }
}
