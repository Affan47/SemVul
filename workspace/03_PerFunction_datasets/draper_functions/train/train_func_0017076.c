starfish_draw (Display *dpy, Window window, void *closure)
{
  struct state *st = (struct state *) closure;
  struct starfish *s = st->starfish;
  time_t now;

  run_starfish (st, s);

  if (st->duration > 0)
    {
      if (st->start_time == 0)
        st->start_time = time ((time_t) 0);
      now = time ((time_t) 0);
      if (st->start_time + st->duration < now)
        {
          st->start_time = now;

          free_starfish (s);


          if (! (random () % 10))
            s = reset_starfish (st);
          else
            s = make_window_starfish (st);

	  st->starfish = s;
        }
    }

  return st->delay;
}
