handle(int e) {
  int c = which;
  switch (e) {
  case FL_PUSH:
  case FL_DRAG: {
    int X = (Fl::event_x_root() - x() - BORDER);
    if (X >= 0) X = X/BOXSIZE;
    int Y = (Fl::event_y_root() - y() - BORDER);
    if (Y >= 0) Y = Y/BOXSIZE;
    if (X >= 0 && X < 8 && Y >= 0 && Y < 32)
      c = 8*Y + X;
    else
      c = initial;
    } break;
  case FL_RELEASE:
    done = 1;
    return 1;
  case FL_KEYBOARD:
    switch (Fl::event_key()) {
    case FL_Up: if (c > 7) c -= 8; break;
    case FL_Down: if (c < 256-8) c += 8; break;
    case FL_Left: if (c > 0) c--; break;
    case FL_Right: if (c < 255) c++; break;
    case FL_Escape: which = initial; done = 1; return 1;
    case FL_KP_Enter:
    case FL_Enter: done = 1; return 1;
    default: return 0;
    }
    break;
  default:
    return 0;
  }
  if (c != which) {
    which = (Fl_Color)c; damage(FL_DAMAGE_CHILD);
    int bx = (c%8)*BOXSIZE+BORDER;
    int by = (c/8)*BOXSIZE+BORDER;
    int px = x();
    int py = y();
    int scr_x, scr_y, scr_w, scr_h;
    Fl::screen_xywh(scr_x, scr_y, scr_w, scr_h);
    if (px < scr_x) px = scr_x;
    if (px+bx+BOXSIZE+BORDER >= scr_x+scr_w) px = scr_x+scr_w-bx-BOXSIZE-BORDER;
    if (py < scr_y) py = scr_y;
    if (py+by+BOXSIZE+BORDER >= scr_y+scr_h) py = scr_y+scr_h-by-BOXSIZE-BORDER;
    if (px+bx < BORDER) px = BORDER-bx;
    if (py+by < BORDER) py = BORDER-by;
    position(px,py);
  }
  return 1;
}
