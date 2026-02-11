rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
#if defined(USE_X11)
  if (!clip_to_short(x, y, w, h))
    XFillRectangle(fl_display, fl_window, fl_gc, x, y, w, h);
#elif defined(WIN32)
  RECT rect;
  rect.left = x; rect.top = y;
  rect.right = x + w; rect.bottom = y + h;
  FillRect(fl_gc, &rect, fl_brush());
#elif defined(__APPLE_QUARTZ__)
  CGRect  rect = CGRectMake(x, y, w - 0.9 , h - 0.9);
  CGContextFillRect(fl_gc, rect);
#else
# error unsupported platform
#endif
}
