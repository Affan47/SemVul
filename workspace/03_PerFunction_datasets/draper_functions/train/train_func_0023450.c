resize(int X,int Y,int W,int H) {
  int is_a_move = (X != x() || Y != y());
  int is_a_resize = (W != w() || H != h());
  int resize_from_program = (this != resize_bug_fix);
  if (!resize_from_program) resize_bug_fix = 0;
  if (is_a_move && resize_from_program) set_flag(FORCE_POSITION);
  else if (!is_a_resize && !is_a_move) return;
  if (is_a_resize) {
    Fl_Group::resize(X,Y,W,H);
    if (shown()) {redraw();}
  } else {
    x(X); y(Y);
  }

  if (resize_from_program && is_a_resize && !resizable()) {
    size_range(w(), h(), w(), h());
  }

  if (resize_from_program && shown()) {
    if (is_a_resize) {
      if (!resizable()) size_range(w(),h(),w(),h());
      if (is_a_move) {
        XMoveResizeWindow(fl_display, i->xid, X, Y, W>0 ? W : 1, H>0 ? H : 1);
      } else {
        XResizeWindow(fl_display, i->xid, W>0 ? W : 1, H>0 ? H : 1);
      }
    } else
      XMoveWindow(fl_display, i->xid, X, Y);
  }
}
