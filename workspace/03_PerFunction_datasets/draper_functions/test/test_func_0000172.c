ripples_draw (Display *dpy, Window window, void *closure)
{
  struct state *st = (struct state *) closure;

  if (st->img_loader)
    {
      st->img_loader = load_image_async_simple (st->img_loader, 0, 0, 0, 0, 0);
      if (! st->img_loader) {
        XWindowAttributes xgwa;
        XGetWindowAttributes(st->dpy, st->window, &xgwa);
        st->start_time = time ((time_t) 0);
        st->orig_map = XGetImage (st->dpy, st->window, 0, 0,
                                  xgwa.width, xgwa.height,
                                  ~0L, ZPixmap);
        init_ripples(st, 0, -SPLASH);
      }
      return st->delay;
    }

    if (!st->img_loader &&
        st->start_time + st->duration < time ((time_t) 0)) {
      XWindowAttributes xgwa;
      XGetWindowAttributes(st->dpy, st->window, &xgwa);
      st->img_loader = load_image_async_simple (0, xgwa.screen, st->window,
                                                st->window, 0, 0);
      st->start_time = time ((time_t) 0);
      return st->delay;
    }

    if (st->rate > 0 && (st->iterations % st->rate) == 0)
      add_drop(st, ripple_blob, -SPLASH);
    if (st->stir)
      add_drop(st, ripple_stir, -SPLASH);
    if (st->box > 0 && (random() % st->box) == 0)
      add_drop(st, ripple_box, -SPLASH);

    ripple(st);
    DisplayImage(st);

    st->iterations++;

    return st->delay;
}
