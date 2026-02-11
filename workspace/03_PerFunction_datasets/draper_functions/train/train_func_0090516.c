handle_key(int key) {
  int h1 = h()-Fl::box_dh(box())-6;
  Fl_Color_Chooser* c = (Fl_Color_Chooser*)parent();

  int Y = int((1-c->value()) * h1);
  if (Y < 0) Y = 0; else if (Y > h1) Y = h1;

  switch (key) {
    case FL_Up :
      Y -= 3;
      break;
    case FL_Down :
      Y += 3;
      break;
    default :
      return 0;
  }

  double Yf;
  Yf = 1-((double)Y/(double)h1);
  if (c->hsv(c->hue(),c->saturation(),Yf)) c->do_callback();

  return 1;
}
