butCan_redrawn(ButWin *win, int x,int y, int w,int h)  {
  Can  *can = win->iPacket;

  assert(MAGIC(win));
  if (can == NULL)
    return;
  assert(MAGIC(can));
  if (can->but == NULL)
    return;
  assert(MAGIC(can->but));
  assert(MAGIC(can->parent));
  if (x < win->xOff)  {
    w -= win->xOff - x;
    x = win->xOff;
  }
  if (y < win->yOff)  {
    h -= win->yOff - y;
    y = win->yOff;
  }
  if (x + w > win->xOff + win->w)
    w = win->xOff + win->w - x;
  if (y + h > win->yOff + win->h)
    h = win->yOff + win->h - y;
  butWin_redraw(can->parent, can->but->x + x - win->xOff,
		can->but->y + y - win->yOff, w, h);
}
