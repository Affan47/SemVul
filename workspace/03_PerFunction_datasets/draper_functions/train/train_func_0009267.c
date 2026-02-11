recolor (state *s, sentence *se)
{
  if (se->fg.flags)
    XFreeColors (s->dpy, s->xgwa.colormap, &se->fg.pixel, 1, 0);
  if (se->bg.flags)
    XFreeColors (s->dpy, s->xgwa.colormap, &se->bg.pixel, 1, 0);

  se->fg.flags  = DoRed|DoGreen|DoBlue;
  se->bg.flags  = DoRed|DoGreen|DoBlue;

  switch (random() % 2)
    {
    case 0:
      se->fg.red    = (random() % 0x8888) + 0x8888;
      se->fg.green  = (random() % 0x8888) + 0x8888;
      se->fg.blue   = (random() % 0x8888) + 0x8888;
      se->bg.red    = (random() % 0x5555);
      se->bg.green  = (random() % 0x5555);
      se->bg.blue   = (random() % 0x5555);
      break;

    case 1:
      se->fg.red    = (random() % 0x4444);
      se->fg.green  = (random() % 0x4444);
      se->fg.blue   = (random() % 0x4444);
      se->bg.red    = (random() % 0x4444) + 0xCCCC;
      se->bg.green  = (random() % 0x4444) + 0xCCCC;
      se->bg.blue   = (random() % 0x4444) + 0xCCCC;
      break;

    default:
      abort();
      break;
    }

  if (s->debug_p)
    se->dark_p = (se->fg.red*2 + se->fg.green*3 + se->fg.blue <
                  se->bg.red*2 + se->bg.green*3 + se->bg.blue);

  if (XAllocColor (s->dpy, s->xgwa.colormap, &se->fg))
    XSetForeground (s->dpy, se->fg_gc, se->fg.pixel);
  if (XAllocColor (s->dpy, s->xgwa.colormap, &se->bg))
    XSetBackground (s->dpy, se->fg_gc, se->bg.pixel);
}
