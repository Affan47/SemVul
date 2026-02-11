trig (Display *dpy, Window window, struct state *st)
{
  int xmid = st->width / 2;
  int ymid = st->height / 2;


    {
      int tmp;
      int angle = st->d_angle + st->d_angle_offset;
      st->x1 = (st->sins [pmod(angle * st->factor1, 360)] * xmid) + xmid;
      st->y1 = (st->coss [pmod(angle * st->factor1, 360)] * ymid) + ymid;
      st->x2 = (st->sins [pmod(angle * st->factor2 + st->offset, 360)] * xmid) + xmid;
      st->y2 = (st->coss [pmod(angle * st->factor2 + st->offset, 360)] * ymid) + ymid;
      XDrawLine(dpy, window, st->draw_gc, st->x1, st->y1, st->x2, st->y2);
      tmp = (int) 360 / (2 * st->density * st->factor1 * st->factor2);
      if (tmp == 0)
	tmp = 1;
      st->d_angle += st->dir * tmp;
    }

  if (st->d_angle < -360 || st->d_angle > 360)
    st->dstate = LINGER;
}
