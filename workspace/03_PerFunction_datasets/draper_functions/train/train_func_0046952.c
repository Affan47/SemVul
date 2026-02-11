idle() {
  if (!window()->visible()) return 0;
  if (drawn < nextline) {
    window()->make_current();
    int yy = drawn+y()+4;
    if (yy >= sy && yy <= sy+sh) erase_box();
    fl_draw_image_mono(buffer+drawn*W,x()+3,yy,W,1,1,W);
    drawn++;
    return 1;
  }
  if (nextline < H) {
    if (!buffer) buffer = new uchar[W*H];
    double yy = Y+(H/2-nextline)*scale/W;
    double yi = yy; if (julia) yy = jY;
    uchar *p = buffer+nextline*W;
    for (int xi = 0; xi < W; xi++) {
      double xx = X+(xi-W/2)*scale/W;
      double wx = xx; double wy = yi;
      if (julia) xx = jX;
      for (int i=0; ; i++) {
	if (i >= iterations) {*p = 0; break;}
	double t = wx*wx - wy*wy + xx;
	wy = 2*wx*wy + yy;
	wx = t;
	if (wx*wx + wy*wy > 4) {
	  wx = t = 1-double(i)/(1<<10);
	  if (t <= 0) t = 0; else for (i=brightness; i--;) t*=wx;
	  *p = 255-int(254*t);
	  break;
	}
      }
      p++;
    }
    nextline++;
    return nextline < H;
  }
  return 0;
}
