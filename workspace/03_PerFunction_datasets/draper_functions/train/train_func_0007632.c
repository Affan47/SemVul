draw_image(struct state *st, Drawable curr_window)
{
  int i, j;
  int x, y;

  for(i = 0; i < st->max_src; i++) {

    if(st->source[i] == NULL)
      continue;

    XSetForeground(st->dpy, st->gcDraw, st->source[i]->color);

    if(st->source[i]->inv_rate > 0) {

      if(st->max_searcher > 0) {
      x = (int) X(st->source[i]->r.x);
      y = (int) Y(st->source[i]->r.y);
      j = st->dx * (MAX_INV_RATE + 1 - st->source[i]->inv_rate) / (2 * MAX_INV_RATE);
      if(j == 0)
	j = 1;
      XFillArc(st->dpy, curr_window, st->gcDraw, x - j, y - j, 2 * j, 2 * j, 0, 360 * 64);
      }}

    for(j = 0; j < st->source[i]->n; j++) {

      if(st->source[i]->yv[j].v == 2)
	continue;


      x =  X(st->source[i]->r.x + 1 + j) + RND(st->dx);
      y = Y(st->source[i]->r.y + st->source[i]->yv[j].y) + RND(st->dy);
      XFillArc(st->dpy, curr_window, st->gcDraw, x - 2, y - 2, 4, 4, 0, 360 * 64);
    }

  }

  for(i = 0; i < st->max_searcher; i++)
    draw_searcher(st, curr_window, i);

}
