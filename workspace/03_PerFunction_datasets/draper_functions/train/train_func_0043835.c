color_cb(Fl_Widget* button, void* v) {
  Fl_Color c;
  switch ((fl_intptr_t)v) {
  case 0: c = FL_BACKGROUND2_COLOR; break;
  case 1: c = FL_SELECTION_COLOR; break;
  default: c = FL_FOREGROUND_COLOR; break;
  }
  uchar r,g,b; Fl::get_color(c, r,g,b);
  if (fl_color_chooser(0,r,g,b)) {
    Fl::set_color(c,r,g,b); Fl::redraw();
    button->labelcolor(fl_contrast(FL_BLACK,c));
    button->redraw();
  }
}
