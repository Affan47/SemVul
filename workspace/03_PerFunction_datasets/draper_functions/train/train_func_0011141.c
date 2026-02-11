send(Fl_Widget* o, int event) {
  if (o->type() < FL_WINDOW) return o->handle(event);
  switch ( event )
  {
  case FL_DND_ENTER:
  case FL_DND_DRAG:

    event = (o->contains(Fl::belowmouse())) ? FL_DND_DRAG : FL_DND_ENTER;
  }
  int save_x = Fl::e_x; Fl::e_x -= o->x();
  int save_y = Fl::e_y; Fl::e_y -= o->y();
  int ret = o->handle(event);
  Fl::e_y = save_y;
  Fl::e_x = save_x;
  switch ( event )
  {
  case FL_ENTER:
  case FL_DND_ENTER:


    if (!o->contains(Fl::belowmouse())) Fl::belowmouse(o);
    break;
  }
  return ret;
}
