helix (Display *dpy, Window window, struct state *st)
{
  int xmid = st->width / 2;
  int ymid = st->height / 2;
  int limit = 1 + (360 / gcd (360, st->d_angle));

  if (st->i == 0)
    {
      st->x1 = xmid;
      st->y1 = ymid + st->radius2;
      st->x2 = xmid;
      st->y2 = ymid + st->radius1;
      st->angle = 0;
    }


    {
      int tmp;
#define pmod(x,y) (tmp=((x) % (y)), (tmp >= 0 ? tmp : (tmp + (y))))

      st->x1 = xmid + (((double) st->radius1) * st->sins [pmod ((st->angle * st->factor1), 360)]);
      st->y1 = ymid + (((double) st->radius2) * st->coss [pmod ((st->angle * st->factor2), 360)]);
      XDrawLine (dpy, window, st->draw_gc, st->x1, st->y1, st->x2, st->y2);
      st->x2 = xmid + (((double) st->radius2) * st->sins [pmod ((st->angle * st->factor3), 360)]);
      st->y2 = ymid + (((double) st->radius1) * st->coss [pmod ((st->angle * st->factor4), 360)]);
      XDrawLine (dpy, window, st->draw_gc, st->x1, st->y1, st->x2, st->y2);
      st->angle += st->d_angle;
    }
    st->i++;

    if (st->i >= limit)
      st->dstate = LINGER;
}
