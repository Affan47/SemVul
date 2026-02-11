hotspot(int X, int Y, int offscreen) {
  int mx,my;


  Fl::get_mouse(mx,my);
  X = mx-X; Y = my-Y;


  if (!offscreen) {
    int scr_x, scr_y, scr_w, scr_h;
    Fl::screen_work_area(scr_x, scr_y, scr_w, scr_h);

    int top = 0;
    int left = 0;
    int right = 0;
    int bottom = 0;

    if (border()) {
#ifdef WIN32
      if (size_range_set && (maxw != minw || maxh != minh)) {
        left = right = GetSystemMetrics(SM_CXSIZEFRAME);
        top = bottom = GetSystemMetrics(SM_CYSIZEFRAME);
      } else {
        left = right = GetSystemMetrics(SM_CXFIXEDFRAME);
        top = bottom = GetSystemMetrics(SM_CYFIXEDFRAME);
      }
      top += GetSystemMetrics(SM_CYCAPTION);
#elif defined(__APPLE__)
      top = 24;
      left = 2;
      right = 2;
      bottom = 2;
#else


      top = 20;
      left = 4;
      right = 4;
      bottom = 8;
#endif
    }

    if (X+w()+right > scr_w+scr_x) X = scr_w+scr_x-right-w();
    if (X-left < scr_x) X = left + scr_x;
    if (Y+h()+bottom > scr_h+scr_y) Y = scr_h+scr_y-bottom-h();
    if (Y-top < scr_y) Y = top + scr_y;

    if (X==x()) x(X-1);
  }

  position(X,Y);
}
