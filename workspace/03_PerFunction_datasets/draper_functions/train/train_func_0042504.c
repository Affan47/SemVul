throb (struct state *st, Drawable window, struct throbber *t)
{
  t->size += t->speed;
  if (t->size <= (t->thickness / 2))
    {
      t->speed = -t->speed;
      t->size += (t->speed * 2);
    }
  else if (t->size > t->max_size)
    {
      t->speed = -t->speed;
      t->size += (t->speed * 2);
      t->fuse--;
    }

  if (t->fuse <= 0)
    {
      XFreeGC (st->dpy, t->gc);
      memset (t, 0, sizeof(*t));
      free (t);
      return -1;
    }
  else
    {
      t->draw (st, window, t);
      return 0;
    }
}
