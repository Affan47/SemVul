move_right (Client * c)
{
  if (c && c->isnotile)
    {
      int max_x = DisplayWidth (dpy, c->screen->num) - c->dx - (2 * BORDER);

      if (c->screen->bigmr[c->screen->desktop])
	c->x += (DisplayWidth (dpy, c->screen->num) / 20);
      else
	c->x++;

      if (c->x > max_x)
	c->x = max_x;

      XMoveWindow (dpy, c->parent, c->x, c->y);
      sendconfig (c);
    }
}
