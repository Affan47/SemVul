eraser_draw (eraser_state *st, Bool first_p)
{
  double now = (first_p ? st->start_time : double_time());
  double duration = st->stop_time - st->start_time;

  st->prev_ratio = st->ratio;
  st->ratio = (now - st->start_time) / duration;

  if (st->ratio > 1.0)
    st->ratio = 1.0;

  st->fn (st);
  XSync (st->dpy, False);

  return (st->ratio < 1.0);
}
