xlyap_draw (Display *dpy, Window window, void *closure)
{
  struct state *st = (struct state *) closure;
  int i;

  if (!st->run && st->reset_countdown) {
    st->reset_countdown--;
    if (st->reset_countdown)
      return 1000000;
    else {
      do_defaults (st);
      do_preset (st, (random() % NBUILTINS));
      Clear (st);
      init_data(st);
      init_color(st);
      resize (st);
      st->frame = 0;
      st->run = 1;
    }
  }

  for (i = 0; i < 1000; i++)
    if (complyap(st) == TRUE)
      {
        st->run = 0;
        st->reset_countdown = st->linger;
        break;
      }
  return st->delay;
}
