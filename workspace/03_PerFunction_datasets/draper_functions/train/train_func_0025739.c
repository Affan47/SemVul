SetWinDev(dev)
device *dev;
{ int i, x, y;
  unsigned int h, w;
  char *z;


  dev->AddColor = winAddColor;
  dev->SetColor = winSetColor;
  dev->ClearScreen = winClearScreen;
  dev->TextDim = winTextDim;
  dev->DoText = winDoText;
  dev->DrawPoint = winDrawPoint;
  dev->DrawLine = winDrawLine;
  dev->DrawPatch = winDrawPatch;
  dev->wrapup = winwrapup;
  dev->makewin = winmakewin;
  dev->ticklength = 5;
  h = 400; w = 600;
  dev->defth = h;
  dev->deftw = w;

  if (nogr) return;

  scr = DefaultScreen(dpy);
  dep = DefaultDepth(dpy,scr);
  comap = DefaultColormap(dpy,scr);
  attr.background_pixel = WhitePixel(dpy,scr);
  mask = CWBackPixel;

  z = XGetDefault(dpy,"locfit","regfont");
  regfont = (z==NULL) ? XLoadQueryFont(dpy,"8x13") :
                        XLoadQueryFont(dpy,z);
  z = XGetDefault(dpy,"locfit","bigfont");
  bigfont = (z==NULL) ? XLoadQueryFont(dpy,"10x20") :
                        XLoadQueryFont(dpy,z);
  if (bigfont==NULL) bigfont = regfont;
  if (regfont==NULL) regfont = bigfont;
  if (bigfont==NULL) WARN(("couldn't load any fonts"));

  z = XGetDefault(dpy,"locfit","geometry");
  XParseGeometry(z,&x,&y,&w,&h);

  dev->defth = h;
  dev->deftw = w;
}
