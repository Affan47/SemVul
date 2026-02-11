draw_string (state *st)
{
  char buf[40];
  int direction, ascent, descent;
  int bot = st->scrollers[0].rect.y;
  const char *fmt = "%08X";
  int i;


  for (i = 0; i < countof (st->fonts); i++)
    {
      XCharStruct overall;
      int x, y, w, h;

      if (! st->fonts[i]) continue;

      sprintf (buf, fmt, 0);
      XTextExtents (st->fonts[i], buf, strlen(buf),
                    &direction, &ascent, &descent, &overall);
      sprintf (buf, "%08X", st->scrollers[0].value);

      w = overall.width;
      h = ascent + descent + 1;
      x = (st->xgwa.width - w) / 2;
      y = (bot - h) / 2;

      if (y + h + 10 <= bot && x > -10)
        {
          XSetFont (st->dpy, st->text_gc, st->fonts[i]->fid);
          XFillRectangle (st->dpy, st->window, st->erase_gc,
                          x-w, y, w*3, h);
          XDrawString (st->dpy, st->window, st->text_gc,
                       x, y + ascent, buf, strlen(buf));
          break;
        }
    }
}
