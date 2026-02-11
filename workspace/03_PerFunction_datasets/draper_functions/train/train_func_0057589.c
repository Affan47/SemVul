anemotaxis_draw (Display *disp, Window window, void *closure)
{
  struct state *st = (struct state *) closure;
  XWindowAttributes wa;
  int w, h;


  XGetWindowAttributes(st->dpy, st->window, &wa);

  w = wa.width;
  h = wa.height;

  if(w != st->scrWidth || h != st->scrHeight) {
    st->scrWidth = w;
    st->scrHeight = h;
    st->ax = st->scrWidth / (double) st->max_dist;
    st->ay = st->scrHeight / (2. * st->max_dist);
    st->bx = 0.;
    st->by = 0.;

    if((st->dx = st->scrWidth / (2 * st->max_dist)) == 0)
      st->dx = 1;
    if((st->dy = st->scrHeight / (4 * st->max_dist)) == 0)
      st->dy = 1;
    XSetLineAttributes(st->dpy, st->gcDraw, st->dx / 3 + 1, LineSolid, CapRound, JoinRound);
  }

  XFillRectangle (st->dpy, st->b, st->gcClear, 0, 0, st->scrWidth, st->scrHeight);
  animate_anemotaxis(st, st->b);

#ifdef HAVE_DOUBLE_BUFFER_EXTENSION
  if (st->backb) {
    XdbeSwapInfo info[1];
    info[0].swap_window = st->window;
    info[0].swap_action = XdbeUndefined;
    XdbeSwapBuffers (st->dpy, info, 1);
  }
  else
#endif
    if (st->dbuf)	{
      XCopyArea (st->dpy, st->b, st->window, st->gcClear, 0, 0,
                 st->scrWidth, st->scrHeight, 0, 0);
      st->b = (st->b == st->ba ? st->bb : st->ba);
    }

  return st->delay;
}
