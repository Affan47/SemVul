InitCheckBox(struct XObj *xobj)
{
  unsigned long mask;
  XSetWindowAttributes Attr;


  if (xobj->colorset >= 0) {
    xobj->TabColor[fore] = Colorset[xobj->colorset].fg;
    xobj->TabColor[back] = Colorset[xobj->colorset].bg;
    xobj->TabColor[hili] = Colorset[xobj->colorset].hilite;
    xobj->TabColor[shad] = Colorset[xobj->colorset].shadow;
  } else {
    xobj->TabColor[fore] = GetColor(xobj->forecolor);
    xobj->TabColor[back] = GetColor(xobj->backcolor);
    xobj->TabColor[hili] = GetColor(xobj->hilicolor);
    xobj->TabColor[shad] = GetColor(xobj->shadcolor);
  }

  mask = 0;
  Attr.background_pixel = xobj->TabColor[back];
  mask |= CWBackPixel;
  Attr.cursor = XCreateFontCursor(dpy,XC_hand2);
  mask |= CWCursor;

  xobj->win = XCreateWindow(dpy, *xobj->ParentWin,
		xobj->x, xobj->y, xobj->width, xobj->height,0,
		CopyFromParent, InputOutput, CopyFromParent,
		mask, &Attr);
  xobj->gc = fvwmlib_XCreateGC(dpy,xobj->win,0,NULL);
  XSetForeground(dpy, xobj->gc, xobj->TabColor[fore]);

  if ((xobj->Ffont = FlocaleLoadFont(dpy, xobj->font, ScriptName)) == NULL)
  {
    fprintf(stderr, "%s: Couldn't load font. Exiting!\n", ScriptName);
    exit(1);
  }
  if (xobj->Ffont->font != NULL)
    XSetFont(dpy, xobj->gc, xobj->Ffont->font->fid);

  XSetLineAttributes(dpy, xobj->gc, 1, LineSolid, CapRound, JoinMiter);


  xobj->height = xobj->Ffont->height + 5;
  xobj->width =
    FlocaleTextWidth(xobj->Ffont, xobj->title, strlen(xobj->title)) + 30;
  XResizeWindow(dpy, xobj->win, xobj->width, xobj->height);
  if (xobj->colorset >= 0)
    SetWindowBackground(dpy, xobj->win, xobj->width, xobj->height,
			&Colorset[xobj->colorset], Pdepth,
			xobj->gc, True);
  XSelectInput(dpy, xobj->win, ExposureMask);
}
