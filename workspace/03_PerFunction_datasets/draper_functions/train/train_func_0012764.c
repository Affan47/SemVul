handle(int event) {
  if (event == FL_PUSH && Fl::visible_focus()) {
    Fl::focus(this);
    redraw();
  }

  return handle(event,
		x()+Fl::box_dx(box()),
		y()+Fl::box_dy(box()),
		w()-Fl::box_dw(box()),
		h()-Fl::box_dh(box()));
}
