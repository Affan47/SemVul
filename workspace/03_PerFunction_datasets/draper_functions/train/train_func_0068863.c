stack_animate(Stack *s, Stack *d)
{
  int x1, y1, x2, y2, x, y, ox, oy;
  double dx, dist;
  int start, last, now;
#if 0
  int frames=0;
#endif
  int sn, dn;

  last = start = ms_time();

  sn = stack_count_cards(s);
  dn = stack_count_cards(d);
  stack_card_posn(s, sn-1, &x1, &y1);
  stack_card_posn(d, dn-1, &x2, &y2);
  if (d->num_cards)
  {
    x2 += d->dx;
    y2 += d->dy;
  }
  stack_begin_drag(s, sn-1, x1, y1);
  flush();


  dist = isqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
  dist = dist * 213 / table_width;

  ox = y1;
  oy = x1;
  while (1)
  {
    now = ms_time();
    if (now == last)
      {
	ms_pause();
	continue;
      }

    dx = (now - start) / dist;
    if (dx >= 1)
      break;
    x = (int)(x1+dx*(x2-x1));
    y = (int)(y1+dx*(y2-y1));
    if (x != ox || y != oy)
    {
      stack_continue_drag(sn-1, x, y);
      ox = x;
      oy = y;
      flushsync();
#if 0
      frames++;
#endif
    }
    else
      ms_pause();
  }
  stack_drop(d, sn-1);
  flush();
  now = ms_time();
  last = now - start;
  if (last < 1) last = 1;
#if 0
  printf("%d frames in %d milliseconds = %g ms/f\n",
	 frames, last, (double)last/frames);
#endif
}
