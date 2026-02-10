refresh_choice(struct choice *c)
{
  int w=c->w+BUT_BUTSPACE;
  int h=dri.dri_Font->ascent+dri.dri_Font->descent+BUT_VSPACE;
  XSetForeground(dpy, gc, dri.dri_Pens[TEXTPEN]);
  XDrawString(dpy, c->win, gc, BUT_BUTSPACE/2,
	      dri.dri_Font->ascent+BUT_VSPACE/2, c->text, c->l);
  XSetForeground(dpy, gc, dri.dri_Pens[(c==selected && depressed)?
				     SHADOWPEN:SHINEPEN]);
  XDrawLine(dpy, c->win, gc, 0, 0, w-2, 0);
  XDrawLine(dpy, c->win, gc, 0, 0, 0, h-2);
  XSetForeground(dpy, gc, dri.dri_Pens[(c==selected && depressed)?
				     SHINEPEN:SHADOWPEN]);
  XDrawLine(dpy, c->win, gc, 1, h-1, w-1, h-1);
  XDrawLine(dpy, c->win, gc, w-1, 1, w-1, h-1);
  XSetForeground(dpy, gc, dri.dri_Pens[BACKGROUNDPEN]);
  XDrawPoint(dpy, c->win, gc, w-1, 0);
  XDrawPoint(dpy, c->win, gc, 0, h-1);
}
