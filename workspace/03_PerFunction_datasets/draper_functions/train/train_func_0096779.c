computerPic_draw(But *but, int x,int y, int w,int h)  {
  XPoint  points[4];
  ButWin  *win = but->win;
  Display  *dpy = butEnv_dpy(butWin_env(win));
  Window  xwin = butWin_xwin(win);
  GC  gc = butEnv_gc(butWin_env(win));
  int  h2 = but->h / 2, h3 = but->h / 3, h12 = but->h / 12;
  int  w6 = but->w / 6, w9 = but->w / 9;

  x = but->x;
  y = but->y;
  w = but->w;
  h = but->h;
  y += (h - (h12 + h2 + h12 + h3)) / 2;
  points[0].x = x;
  points[0].y = y + h12 + h2 + h3;
  points[1].x = x + w6;
  points[1].y = y + h12 + h2 + h12;
  points[2].x = x + w - w6;
  points[2].y = y + h12 + h2 + h12;
  points[3].x = x + w;
  points[3].y = y + h12 + h2 + h3;
  butEnv_setXFg(butWin_env(win), BUT_BLACK);
  XFillPolygon(dpy, xwin, gc, points, 4, Nonconvex, CoordModeOrigin);
  XFillRectangle(dpy, xwin, gc, x+w6,y+h12, w-2*w6,h2);
  butEnv_setXFg(butWin_env(win), BUT_PBG);
  XFillRectangle(dpy, xwin, gc, x+w6+w9,y+h12*2, w-2*w6-2*w9,h2-h12*2);
}
