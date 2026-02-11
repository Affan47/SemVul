resize(int X,int Y,int W,int H) {


  int dx = X-x();
  int dy = Y-y();
  int dw = W-w();
  int dh = H-h();
  int *p = sizes();

  Fl_Widget::resize(X,Y,W,H);

  int OR = p[5];
  int NR = X+W-(p[1]-OR);
  int OB = p[7];
  int NB = Y+H-(p[3]-OB);

  Fl_Widget*const* a = array();
  p += 8;
  for (int i=children(); i--;) {
    Fl_Widget* o = *a++;
    int xx = o->x()+dx;
    int R = xx+o->w();
    if (*p++ >= OR) xx += dw; else if (xx > NR) xx = NR;
    if (*p++ >= OR) R += dw; else if (R > NR) R = NR;
    int yy = o->y()+dy;
    int B = yy+o->h();
    if (*p++ >= OB) yy += dh; else if (yy > NB) yy = NB;
    if (*p++ >= OB) B += dh; else if (B > NB) B = NB;
    o->resize(xx,yy,R-xx,B-yy);


  }
}
