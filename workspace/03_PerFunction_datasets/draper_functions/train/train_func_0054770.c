mono8_converter(const uchar *from, uchar *to, int w, int delta) {
  int r=ri, g=gi, b=bi;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    to = to+(w-1);
    d = -delta;
    td = -1;
  } else {
    dir = 1;
    d = delta;
    td = 1;
  }
  for (; w--; from += d, to += td) {
    r += from[0]; if (r < 0) r = 0; else if (r>255) r = 255;
    g += from[0]; if (g < 0) g = 0; else if (g>255) g = 255;
    b += from[0]; if (b < 0) b = 0; else if (b>255) b = 255;
    Fl_Color i = fl_color_cube(r*FL_NUM_RED/256,g*FL_NUM_GREEN/256,b*FL_NUM_BLUE/256);
    Fl_XColor& xmap = fl_xmap[0][i];
    if (!xmap.mapped) {if (!fl_redmask) fl_xpixel(r,g,b); else fl_xpixel(i);}
    r -= xmap.r;
    g -= xmap.g;
    b -= xmap.b;
    *to = uchar(xmap.pixel);
  }
  ri = r; gi = g; bi = b;
}
