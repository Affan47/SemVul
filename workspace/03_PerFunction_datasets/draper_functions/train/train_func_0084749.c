quad_wipe (eraser_state *st)
{
  int i;
  if (st->ratio == 0.0)
    {
      st->flip_x = random() & 1;
      st->flip_y = random() & 1;
      st->nlines = st->width + st->height;
      st->lines = (int *) calloc (st->nlines, sizeof(*st->lines));

      for (i = 0; i < st->nlines/4; i++)
        {
          st->lines[i*4]   = i*2;
          st->lines[i*4+1] = st->height - i*2 - (st->height % 2 ? 0 : 1);
          st->lines[i*4+2] = st->height + i*2;
          st->lines[i*4+3] = st->height + st->width - i*2
            - (st->width % 2 ? 0 : 1);
        }
    }

  for (i = st->nlines * st->prev_ratio;
       i < st->nlines * st->ratio;
       i++)
    {
      int x, y, x2, y2;
      if (st->lines[i] < st->height)
        x = 0, y = st->lines[i], x2 = st->width, y2 = y;
      else
        x = st->lines[i] - st->height, y = 0, x2 = x, y2 = st->height;

      if (st->flip_x)
        x = st->width-x, x2 = st->width-x2;
      if (st->flip_y)
        y = st->height-y, y2 = st->height-y2;

      XDrawLine (st->dpy, st->window, st->bg_gc, x, y, x2, y2);
    }

  if (st->ratio >= 1.0)
    {
      free (st->lines);
      st->lines = 0;
    }
}
